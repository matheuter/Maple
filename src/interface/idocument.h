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

#ifndef IDOCUMENT_H
#define IDOCUMENT_H

#include "iobject.h"
#include "iinterface.h"

class QString;
class IDocument;
class IDocumentService;

/**
 * @brief
 */
class IDocumentInterface : public IInterface
{
    Q_OBJECT
public:
    IDocumentInterface(QObject *parent = 0) : IInterface(parent) {}

    virtual IDocument*    getDocument(const QString& path) = 0;
    virtual void  RegisterDocumentService(IDocumentService* factory) = 0;
    virtual void removeDocumentService(IDocumentService* factory) = 0;
    virtual QList<IDocumentService*> list() = 0;
};


/**
 * @brief
 */
class IDocument : public IObject
{
    Q_OBJECT
public:
    IDocument(IObject *parent = 0) : IObject(parent) {}
    virtual ~IDocument() {}

    virtual QString path() = 0;
    virtual void setPath(const QString &filePath) = 0;

    virtual QString name() = 0;
    virtual void setName(const QString &fileName) = 0;

    virtual QString type() = 0;
    virtual void setType(const QString & type) = 0;

    virtual QByteArray data() = 0;
    virtual bool load(const QString &filePath, QTextCodec *codec = 0) = 0;
    virtual bool load(const QString &filePath, const QByteArray &codecName) = 0;

    virtual bool save(const QString & data) = 0;
    virtual bool save() = 0;
    virtual bool saveAs(const QString & data,const QString &filePath) = 0;
    virtual void clear() = 0;

    virtual void lockForRead() = 0;
    virtual void lockForWrite() = 0;
    virtual bool tryLockForRead() = 0;
    virtual bool tryLockForWrite() = 0;
    virtual void unlock() = 0;

    enum FindModeFlag {
        FindNone = 0x00000,
        FindBackward = 0x00001,
        FindCaseSensitively = 0x00002,
        FindWholeWords = 0x00004,
        FindAllowInterrupt = 0x00008,
        FindWrap = 0x00010,
        FindAll = 0x00020
    };
};

/**
 * @brief
 */
class  IDocumentService : public IModule
{
    Q_OBJECT
public:
    IDocumentService(QObject* parent = 0): IModule(parent){}

    virtual QList<QString> getTypes() = 0;
    virtual bool contains(const QString &type) = 0;
    virtual void addType(const QString &type) {}
    virtual void addTypes(const QStringList& types) {}
    virtual IDocument*  create(const QString &path) = 0;
};

#endif // IDOCUMENT_H
