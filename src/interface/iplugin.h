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

#ifndef IPLUGIN_H
#define IPLUGIN_H

#include <QtPlugin>
#include <QStringList>

#include <string>
#include <vector>

#include "iobject.h"
#include "iinterface.h"

class IApplication;

struct PluginDepend
{
    /* 主版本号，用于无法兼容的版本迭代 */
    int m_major;

    /* 次版本号，兼容的版本迭代 */
    int m_minor;

    /* 修补版本号，问题修复*/
    int m_patch;

    /* 插件唯一标识 */
    std::string m_identify;
};

struct PluginInfomation
{
    /* 作者姓名 */
    std::string m_anchor;

    /* 插件描述 */
    std::string m_information;

    /* 插件唯一标识 */
    std::string m_identify;

    /* 主版本号，用于无法兼容的版本迭代 */
    int m_major;

    /* 次版本号，兼容的版本迭代 */
    int m_minor;

    /* 修补版本号，问题修复*/
    int m_patch;

    /* 插件依赖 */
    std::vector<PluginDepend> m_dependList;
};

class Q_DECL_EXPORT IPlugin : public IObject
{
public:
    IPlugin() = default;
    virtual ~IPlugin(){}

    IPlugin(const IPlugin&) = delete;
    IPlugin& operator=(const IPlugin&) = delete;

public:
    /*
     * 初始化插件，通过纯虚函数将application指针传入
     */
    virtual bool initize(IApplication *app)
    {
        if(app == nullptr)
        {
            return false;
        }
        m_application = app;
        return true;
    }

    virtual IApplication * getApplication()
    {
        return m_application;
    }

    /*
     * 获取插件相关信息，包括插件自身的信息和插件相关依赖
     */
    PluginInfomation *infomation() const
    {
        return m_infomation;
    }

    /*
     * 设置插件相关信息
     */
    void setInfomation(PluginInfomation *newInfomation)
    {
        m_infomation = newInfomation;
    }

    enum PluginState
    {
      idle,
      starting,
      started,
      stopping,
      stopped,
      excepting,
    };

    enum PluginType
    {
        SCRIPT_PLUGIN,
        DLL_PLUGIN
    };

private:
    PluginInfomation   * m_infomation;
protected:
    IApplication *       m_application;
};

class IPluginModule : public IModule
{
public:
    virtual IPlugin *create() = 0;
};

Q_DECLARE_INTERFACE(IPluginModule, "org.notebook.IPluginModule")

#endif // IPLUGIN_H
