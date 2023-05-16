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

#ifndef IINTERFACE_H
#define IINTERFACE_H

#include "iobject.h"
#include "iapplication.h"

class IActor;

class IPlugin;

namespace Maple {
    class ActorUnit;
}
class  IInterface : public IObject
{
public:
    IInterface(QObject *parent = 0) : IObject(parent) {}
    virtual ~IInterface() {}
    virtual bool initialize(IApplication *app)
    {
        if (!app){
            return false;
        }
        m_application = app;
        return true;
    }
    IApplication *getApplication(){return m_application;}
protected:
    IApplication *m_application;
    Maple::ActorUnit*  m_actorUnit;
};

class IModule : public IObject
{
public:
    IModule(QObject *parent = 0) : IObject(parent) {}
    virtual ~IModule(){}
};

class Q_DECL_EXPORT ISerser : public IObject
{
public:
    ISerser(QObject *parent = 0) : IObject(parent) {}
    virtual ~ISerser(){}
};
#endif // IINTERFACE_H
