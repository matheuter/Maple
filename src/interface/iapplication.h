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

#ifndef IAPPLICATION_H
#define IAPPLICATION_H

#include "iobject.h"

class QString;
class IExtension;
class IPlugin;
class IViewInterface;
class IDocumentInterfa;
class IActionInterface;
class IOptionInterface;
class IDockInterface;
class QMainWindow;
class QSettings;
class MainWindow;
class PluginManagerInterface;
class IDocumentInterface;
class IModule;

class IApplication : public IObject
{
public:
    virtual                        ~IApplication() {}
    virtual IViewInterface         *viewInterface() = 0;
    virtual IActionInterface       *actionInterface() = 0;
    virtual PluginManagerInterface *pluginInterface() = 0;
    virtual IOptionInterface       *optionInterface() = 0;
    virtual IDockInterface         *dockInterface() = 0;
    virtual MainWindow             *mainWindow() const = 0;

};

#endif // IAPPLICATION_H
