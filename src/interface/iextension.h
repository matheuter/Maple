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

#ifndef EXTENSION_H_
#define EXTENSION_H_

#ifdef __GNUC__
#include <cxxabi.h>
#endif

#include <cstdlib>
#include <typeinfo>
#include <typeindex>

#include <QObject>
#include <QHash>
#include <QList>

#include "configure.h"

class QStringList;

class Q_DECL_EXPORT IExtension
{
public:
    virtual ~IExtension(){}
    typedef QMap<MeteGroup, QHash<QString, QObject*> > MeteMap;
    virtual void registerObject(const QString &meta,
                                MeteGroup meteGroup,
                                QObject *obj) = 0;
    virtual void removeObject(const QString &meta,MeteGroup meteGroup) = 0;
    virtual void removeObject(const QString &meta) = 0;
    virtual void removeObject(const QObject *object) = 0;
    virtual bool containsObject(const QString &meta)const = 0;

    virtual QObject *getObjectPointer(const QString &meta,MeteGroup meteGroup) const = 0;
    virtual QObject *getObjectPointer(const QString &meta) const = 0;

    virtual QObject *getCurrentViewPointer() const = 0;
    virtual void setCurrentViewPointer(QObject *)  = 0;
    virtual QStringList objectMetaList(MeteGroup meteGroup) const = 0;
};

#endif
