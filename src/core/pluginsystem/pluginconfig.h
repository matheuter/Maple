#ifndef PLUGINCONFIG_H
#define PLUGINCONFIG_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
// Windows
#define MAPLE_WINDOWS
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif

#elif defined(linux) || defined(__linux)
// Linux
#define MAPLE_LINUX
#elif defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)
// MacOS
#define MAPLE_MACOS
#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
// FreeBSD
#define MAPLE_FREEBSD
#else
// Unsupported system
#error This operating system is not supported by this library

#endif

#ifdef MAPLE_WINDOWS
#define MAPLE_EXTENSION "dll"
#elif defined(MAPLE_MACOS)
#define MAPLE_EXTENSION "dylib"
#elif defined(MAPLE_LINUX) || defined(MAPLE_FREEBSD)
#define MAPLE_EXTENSION "so"
#else
// unknown library file type
#error Unknown library file extension for this operating system
#endif

#if defined(MAPLE_WINDOWS)
#ifndef MAPLE_STATIC
// Windows platforms
#ifdef MAPLE_EXPORTS
// From DLL side, we must export
#define MAPLE_API __declspec(dllexport)
#else
// From client application side, we must import
#define MAPLE_API __declspec(dllimport)
#endif
// For Visual C++ compilers, we also need to turn off this annoying C4251 warning.
// You can read lots ot different things about it, but the point is the code will
// just work fine, and so the simplest way to get rid of this warning is to disable it
#ifdef _MSC_VER
#pragma warning(disable : 4251)
#endif
#else
// No specific directive needed for static build
#define MAPLE_API
#endif
#else
// Other platforms don't need to define anything
#define MAPLE_API
#endif


#include <string>
#include <map>
#include <iostream>

namespace {   // Force internal linkage
template<typename Base, typename Derived, typename Key = std::string>
struct reg_placeholder {
    static bool reg;
};
template<typename Base, typename Derived, typename Key>
bool reg_placeholder<Base, Derived, Key>::reg = false;
}


template<typename Base, typename Derived>
struct PluginFactory {
    static Base* build() { return new Derived; }
};

template<typename Base, typename Key = std::string>
class PluginBuilder {
public:
    typedef Base* ( *FactoryFunc ) ();
    typedef std::map<Key, FactoryFunc> FactoryMap;
    static FactoryMap _map;
    //static FactoryMap factoryMap;

    static FactoryMap& factoryMap() {
        //static FactoryMap _map;
        return _map;
    }

    static Base* build(const Key& key) {
        typename FactoryMap::const_iterator it = factoryMap().find(key);
        return (it != factoryMap().end() ? (it->second)() : NULL);
    }

    template<typename Derived>
    static bool load(const Key& key, FactoryFunc func = 0) {
        if(!func) func = PluginFactory<Base, Derived>::build;
        std::cout << "Loading " << key <<' '<<&(factoryMap())<<std::endl;
        // Insert it, but don't overwrite
        // TODO: Warn of conflicts
        return !(factoryMap().insert(typename FactoryMap::value_type(key, func)).second);
    }
};

#define INIT_PLUGIN_BUILDER \
    template<typename Base, typename Key> \
    typename PluginBuilder<Base, Key>::FactoryMap PluginBuilder<Base, Key>::_map = PluginBuilder<Base, Key>::FactoryMap();

#define REGISTER_PLUGIN(Base, Derived) \
    namespace {                          \
    template<> bool reg_placeholder<Base, Derived>::reg = PluginBuilder<Base>::load<Derived>(#Derived); \
    }

//class Animal {
//public:
//    Animal() {}
//    virtual ~Animal() {}
//    virtual void speak() = 0;
//    static std::vector<std::string> kinds() {
//        std::vector<std::string> ret;
//        for(PluginBuilder<Animal>::FactoryMap::const_iterator it = PluginBuilder<Animal>::factoryMap().begin(); it != PluginBuilder<Animal>::factoryMap().end(); ++it)
//            ret.push_back(it->first);
//        return ret;
//    }
//    static Animal* create(const std::string& kind) {
//        return PluginBuilder<Animal>::build(kind);
//    }
//};

#endif // PLUGINCONFIG_H
