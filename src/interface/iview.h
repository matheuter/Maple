/**
 ** This file is part of the NoteBook project.
 ** Copyright 2022 ji wang <matheuter@gmail.com>.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU Lesser General Public License as
 ** published by the Free Software Foundation, either version 3 of the
 ** License, or (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU Lesser General Public License for more details.
 **
 ** You should have received a copy of the GNU Lesser General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

#ifndef IVIEWINTERFACE_H
#define IVIEWINTERFACE_H

#include <QMenu>
#include <QList>

#include "iextension.h"
#include "iinterface.h"
#include "idocument.h"

class QString;
class IDocument;
class IDocumentView;

/**
 * @brief this class is an abstract interface to describe the viewService interface should be exposed
 * if you want add new View like DocumentView,You should inherit this class and implement the associated interface
 * This service is usually defined with the document service, of course, you can also use the system default View
 */
class IView : public IObject
{
    Q_OBJECT
public:
    IView(QObject *parent = 0) : IObject(parent) {}

    virtual QWidget   *widgetInstance() = 0;

};

class  IViewService : public IModule
{
    Q_OBJECT
public:
    IViewService(QObject *parent = 0) : IModule(parent) {}
    virtual ~IViewService(){}

    virtual QList<QString> getTypes() = 0;
    virtual bool contains(const QString &type) = 0;
    virtual void addType(const QString &type) {}

    virtual IDocumentView * createView(IDocument* doc) = 0;
};
/**
 * @brief This virtual base class is our viewmodel, and in fact, it is not a Widget directly, but encapsulates a Widget internally
 */
class IDocumentView : public IView
{
    Q_OBJECT
public:
    IDocumentView(QObject *parent = 0) : IView(parent) {}
    virtual ~IDocumentView(){}
    virtual bool reload() = 0;
    virtual bool save() = 0;
    virtual bool saveAs(const QString &filePath) = 0;
    virtual IDocument* getDocument() = 0;
};

class  ITextView : public IDocumentView
{
    Q_OBJECT
public:
    ITextView(QObject *parent = 0) : IDocumentView(parent) {}
    virtual ~ITextView(){}

    virtual int line() const = 0;
    virtual int column() const = 0;
    virtual int utf8Position() const = 0;
    virtual QByteArray utf8Data() const = 0;
    virtual void gotoLine(int line, int column, bool center = false) = 0;
};

class  IBinaryView : public IDocumentView
{
    Q_OBJECT
public:
    IBinaryView(QObject *parent = 0) : IDocumentView(parent) {}
    virtual int line() const = 0;
    virtual int column() const = 0;
    virtual int utf8Position() const = 0;
    virtual QByteArray utf8Data() const = 0;
    virtual void gotoLine(int line, int column, bool center = false) = 0;
};

class  IViewInterface : public IInterface
{
public:
    IViewInterface(QObject *parent = 0) : IInterface(parent) {}

    virtual void     registerViewService(IViewService *) = 0;
    virtual void     removeService(IViewService *) = 0;
    virtual QList<IViewService*> ServiceList() const = 0;

    virtual IDocumentView *insertDocumentView(IDocument*) = 0;
    virtual void removeDocumentView(const QString& id) = 0;
    virtual void removeDocumentView(IDocumentView *g) = 0;
};

#endif // IVIEWINTERFACE_H
