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

#include <QList>
#include <string>
#include <QPluginLoader>
#include <QDir>
#include <QVariantMap>
#include <QJsonArray>

#include "pluginmanager.h"
#include "iplugin.h"

class PluginManagerInterfacePrivate
{
public:
    ~PluginManagerInterfacePrivate(){}
    bool check(const QString& path);

    QHash<QString, QVariant> m_names;
    QHash<QString, QVariant> m_versions;
    QHash<QString, QVariantList> m_dependencies;

    QAction         *m_aboutPluginsAct;
    QHash<QString,IInterface*> m_interfaceMap;
    QHash<QString,IPlugin*> m_filePluginMap;
    QHash<QString,QPluginLoader*> m_pluginLoaderMap;
};

// Detecting plugin dependencies
bool PluginManagerInterfacePrivate::check(const QString& path)
{
    bool status = true;
    foreach (QVariant item, m_dependencies.value(path)) {
        QVariantMap map = item.toMap();

        // Dependent plugin name version path
        QVariant name =    map.value("name");
        QVariant version = map.value("version");
        QString path =     m_names.key(name);

        //Check whether plug-ins depend on other plug-in
        if (!m_names.values().contains(name)) {
            qDebug() << Q_FUNC_INFO << "  Missing dependency:" << name.toString() << "  for plugin" << path;
            status = false;
            continue;
        }
        if (m_versions.value(path) != version) {
            qDebug() << Q_FUNC_INFO << "  Version mismatch:" << name.toString() << "  version"
                     << m_versions.value(m_names.key(name)).toString() << "but" << version.toString() << "  required for plugin  " << path;
            status = false;
            continue;
        }
        if (!check(path)) {
            qDebug() << Q_FUNC_INFO << "  Corrupted dependency:" << name.toString() << "  for plugin  " << path;
            status = false;
            continue;
        }
    }
    return status;
}

// Load all plugins
void PluginManagerInterface::loadAll(const QString &dir)
{
    QDir path = QDir(dir);
    path.cd("plugins");

    // Initialize the metadata in the plugins
    foreach (QFileInfo info, path.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks))
        scan(info.absoluteFilePath());

    // load plugins
    foreach (QFileInfo info, path.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks))
        load(info.absoluteFilePath());
}

// Scan the plugin metadata in the JSON file
void PluginManagerInterface::scan(const QString& path)
{
    if (!QLibrary::isLibrary(path))
        return;

    // Get metadata (name version dependence)
    QPluginLoader *loader = new QPluginLoader(path);
    QJsonObject json = loader->metaData().value("MetaData").toObject();

    d->m_names.insert(path, json.value("name").toVariant());
    d->m_versions.insert(path, json.value("version").toVariant());
    d->m_dependencies.insert(path, json.value("dependencies").toArray().toVariantList());

    delete loader;
    loader = nullptr;
}

// load plugin
bool PluginManagerInterface::load(const QString& path)
{
    //Check whether the path is the library path
    if (!QLibrary::isLibrary(path))
        return false ;

    // Detecting plugin dependencies
    if (!d->check(path))
        return false;

    // Before loading the plugin, Verify that the plugin loads properly
    QPluginLoader *loader = new QPluginLoader(path);
    if (loader->load()){
        IPluginModule * pFactory = qobject_cast<IPluginModule*>(loader->instance());
        if (pFactory){
            //If it inherits from Plugin, it is considered its own plugin (to prevent external plugin injection)
            IPlugin *plugin = pFactory->create();
            if (plugin) {
                d->m_filePluginMap.insert(plugin->infomation()->m_identify.c_str(),plugin);
                d->m_pluginLoaderMap.insert(path,loader);
                //connect(plugin,SIGNAL(sender(Message&)),this,SLOT(Messagerocessing(Message&)));
                //connect(plugin,SIGNAL(sender(MultMessage&)),this,SLOT(Messagerocessing(MultMessage&)));
                return true;
            }
            else {
                delete loader;
                loader = nullptr;
            }
        }
    }
    else {
        delete loader;
        loader = nullptr;
    }
    return false;
}

void PluginManagerInterface::unload(const QString& path)
{
    QPluginLoader *loader = d->m_pluginLoaderMap.value(path);

    // unload the plugin and remove it from the internal data structure
    if (loader->unload()) {
        //d->m_filePluginMap.remove(qobject_cast<IPlugin*>(loader->instance())->infomation()->m_identify);
        d->m_pluginLoaderMap.remove(path);
        delete loader;
        loader = nullptr;
    }
}

void PluginManagerInterface::unloadAll(const QString &dir)
{

}

QList<IPlugin *> PluginManagerInterface::plugins()
{
    return d->m_filePluginMap.values();
}

void PluginManagerInterface::pluginInfomation(const QString &path)
{

}

void PluginManagerInterface::registerInterface(QList<IInterface *> list)
{
    for (auto obj: list)
        d->m_interfaceMap.insert(obj->objectName(),obj);
}

PluginManagerInterface::PluginManagerInterface():
    d(new PluginManagerInterfacePrivate)
{
}

