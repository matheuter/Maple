///**
// ** This file is part of the NoteBook project.
// ** Copyright 2022 ji wang <matheuter@gmail.com>.
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU Lesser General Public License as
// ** published by the Free Software Foundation, either version 3 of the
// ** License, or (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU Lesser General Public License for more details.
// **
// ** You should have received a copy of the GNU Lesser General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **/

//#ifndef IDOCUMENT_H
//#define IDOCUMENT_H

//#include <QStringList>

//#include "iobject.h"
//#include "iinterface.h"


//class QString;
//class IDocument;
//class IDocumentService;

////class  IDocumentInterface : public IInterface
////{
////    Q_OBJECT
////public:
////    IDocumentInterface(QObject *parent = 0) : IInterface(parent) {}

////    virtual IDocument*    getDocument(const QString& path) = 0;
////    virtual void  RegisterDocumentService(IDocumentService* factory) = 0;
////    virtual void removeDocumentService(IDocumentService* factory) = 0;
////    virtual QList<IDocumentService*> list() = 0;
////};


//class IDocument : public QObject
//{
//    Q_OBJECT
//public:
//    IDocument(QObject *parent = 0) : QObject(parent) {}
//    virtual ~IDocument() {}
//    virtual QByteArray data() = 0;
//    virtual void setDocumentPath(const QString &filePath) = 0;
//    virtual bool load(const QString &filePath) = 0;
//    virtual bool load() = 0;
//    virtual bool reload() = 0;
//    virtual bool save(const QString & data) = 0;
//    virtual bool saveAs(const QString & data,const QString &filePath) = 0;

//    virtual bool clear() = 0;

//    virtual QString documentPath() const = 0;
//    virtual QString documentName() const = 0;
//    virtual QString documentType() const = 0;
//    virtual QString documentCodeformat() const = 0;
//    virtual void setDocumentCodeformat(const QString &filePath) const = 0;
//};

//class IDocumentService : public IModule
//{
//    Q_OBJECT
//public:
//    IDocumentService(QObject* parent = 0): IModule(parent){}

//    virtual QList<QString> getTypes() = 0;
//    virtual bool contains(const QString &type) = 0;
//    virtual void addType(const QString &type) {}
//    virtual void addTypes(const QStringList& types) {}
//    virtual IDocument*  create(const QString &path) = 0;
//};


//#endif // IDOCUMENT_H
