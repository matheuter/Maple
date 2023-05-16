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

#ifndef IOPITON_H
#define IOPITON_H

#include <QList>

#include "iobject.h"
#include "iview.h"
#include "iinterface.h"

class QAction;

class IOption : public IView
{
    Q_OBJECT
public:
    IOption(QObject *parent = 0) : IView(parent) {}
    virtual void apply() = 0;
};

class IOptionModule : public QObject
{
    Q_OBJECT
public:
    IOptionModule(QObject *parent = 0)
        : QObject(parent)
    {}
    virtual IOption *create() = 0;
};

class  IOptionInterface : public IInterface
{
    Q_OBJECT
public:
    IOptionInterface(QObject *parent = 0) : IInterface(parent) {}
    virtual void addFactory(IOptionModule *factory) = 0;
    virtual void removeFactory(IOptionModule *factory) = 0;
    virtual QList<IOptionModule*> factoryList() const = 0;
    virtual void setAction(QAction *act) = 0;

public slots:
    virtual void optionDialog(bool) = 0;
    virtual void exec() = 0;
signals:
    void applyOption(QString);
};

#endif // IOPITON_H
