//#ifndef APPLICATION_H
//#define APPLICATION_H

//#include <QList>

//#include "iapplication.h"
//#include "idocument.h"
//#include "iextension.h"
//#include "iplugin.h"
//#include "ipreference.h"

//class MainWindow;
//class PluginManagerInterface;
//class ViewInterface;
//class ActionInterface;
//class OptionInterface;

//class PluginManagerInterface;
//class DockInterface;
//class ApplicationPrivate;
//class DocumentInterface;
//class IDocumentInterface;
//class ViewInterface;

//class Application : public IApplication
//{
//    Q_OBJECT

//public:
//    Application();
//    virtual ~Application();
//public:
//    IViewInterface*                 viewInterface()             override;
//    IActionInterface*               actionInterface()           override;
//    virtual IOptionInterface*       optionInterface()           override;
//    virtual Maple::ActorUnit*       actorUnit()                 override ;
//    virtual PluginManagerInterface* pluginInterface()           override;
//    virtual IDockInterface*         dockInterface()             override;
//    virtual MainWindow*             mainWindow() const          override;
//public:
//    void loadPlugins();
//    void initPlugins();
//    void setPluginPath(const QString &path);
//    void setResourcePath(const QString &path);

//    void show();
//private:

//    ApplicationPrivate * d;

//    Application(Application&&) = delete;
//    Application &operator=(const Application &) = delete;

//public:
//    void removeModule(IModule *);
//    void removeModule(std::string &moduleName);
//};


//#endif // APPLICATION_H
