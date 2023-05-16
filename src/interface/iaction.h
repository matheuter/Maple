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

#ifndef IACTION_H
#define IACTION_H

#include <QList>
#include <QMenu>

#include "iextension.h"
#include "iinterface.h"

class QToolBar;
class QAction;
class QWidget;

class  IActionInterface : public IInterface
{
public:
    IActionInterface(QObject *parent = 0) : IInterface(parent) {}
    virtual QMenu* insertContextMenu(const QString &id, const QString &title, QWidget* parent) = 0;
    virtual QMenu* getContextMenu(const QString &id, const QString &title, QWidget* parent) = 0;
    virtual QMenu *insertMenu(QString id, QString title, QString idBefore = QString()) = 0;
    virtual QMenu *getMenuPointer(const QString &id) = 0;
    virtual void removeMenu(QMenu *menu) = 0;

    virtual QList<QString>  menuList() const = 0;
    virtual QToolBar *insertSideBar(const QString &id, const QString &title, const QString &before = QString()) = 0;
    virtual void insertSideBar(QToolBar *toolBar,const QString &before = QString()) = 0;
    virtual QToolBar *getSidebar(const QString &id) = 0;
    virtual void removeSidebarBar(QToolBar* sideBar) = 0;

    virtual QList<QString> sidebarBarList() const = 0;

    virtual void insertViewMenu(int pos, QAction *act) = 0;
};

#endif // IACTION_H
