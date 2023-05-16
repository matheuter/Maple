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

#ifndef PLUGIN_H
#define PLUGIN_H

#include <QObject>

#include "iinterface.h"
#include "iplugin.h"

class QAction;
class QString;
class QPluginLoader;
class PluginManagerInterfacePrivate;

class  PluginManagerInterface : public IInterface
{
    Q_OBJECT
public:
    PluginManagerInterface();
    PluginManagerInterface(const PluginManagerInterface&) = delete;
    PluginManagerInterface(PluginManagerInterface&&) = delete;
    ~PluginManagerInterface(){if(d) delete d;}
    void loadAll(const QString &dir);

    void scan(const QString& path);
    bool load(const QString& path);
    void unload(const QString& path);
    void unloadAll(const QString &dir);
    QList<IPlugin*> plugins();
    void pluginInfomation(const QString& path);
    void registerInterface(QList<IInterface*> list);

private:
    PluginManagerInterfacePrivate *d;
};
#endif // PLUGIN_H
