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

#ifndef IDOCKINTERFACE_H
#define IDOCKINTERFACE_H

#include "iinterface.h"
#include "configure.h"
#include <QDockWidget>

class QWidget;

/**
 * @brief
 */
class  IDockInterface : public IInterface
{
public:
    IDockInterface(QObject *parent = 0) : IInterface(parent) {}
    virtual ~IDockInterface(){}

    /**
    * @brief
    */
    virtual QDockWidget *addDock(QWidget *widget,
                         const QString &title,
                         Qt::DockWidgetArea ares = Qt::LeftDockWidgetArea,
                         Qt::DockWidgetAreas alowedAreas = Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea,
                         QDockWidget::DockWidgetFeatures  features = QDockWidget::AllDockWidgetFeatures) = 0;

    /**
    * @brief
    */
    virtual void removeDock(const QString &title) = 0;

    /**
    * @brief
    */
    virtual void showDock(const QString &title) = 0;

    /**
    * @brief
    */
    virtual void hideDock(const QString &title) = 0;

    /**
    * @brief
    */
    virtual void splitDockWidget(QDockWidget * first,
                                 QDockWidget * second,
                                 Qt::Orientation orientation) = 0;

    /**
    * @brief
    */
    virtual void mergeDockWidget(QDockWidget * first,
                                 QDockWidget * second) = 0;

    /**
    * @brief
    */
    virtual void tabifyDockWidget(QDockWidget * first, DockWidgetArea area) =0;

    /**
    * @brief
    */
    virtual QDockWidget *dockWidget(const QString &title) = 0;
};
#endif // IDOCKINTERFACE_H
