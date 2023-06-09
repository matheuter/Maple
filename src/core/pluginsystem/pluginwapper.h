﻿#ifndef PLUGINWAPPER_H
#define PLUGINWAPPER_H

#if defined(_WIN32) || defined(__CYGWIN32__)
  #include <windows.h>
  typedef HMODULE PluginHandle;
  #define PLUGIN_EXT            ".dll"
  #define PLUGIN_LOAD(fn)       LoadLibrary(fn)
  #define PLUGIN_LOOKUP(hdl, n) GetProcAddress(hdl, n)
  #define PLUGIN_INIT()
  #define PLUGIN_ERR(hdl)
  #define PLUGIN_CLOSE(hdl)     FreeLibrary(hdl)
#else // LINUX || OSX
  #include <dlfcn.h>
  typedef void* PluginHandle;
  #if defined(__APPLE__)
    #define PLUGIN_EXT ".dylib"
  #else
    #define PLUGIN_EXT ".so"
  #endif  // __APPLE__
  #define PLUGIN_LOAD(fn)       dlopen(fn, RTLD_NOW|RTLD_GLOBAL)
  #define PLUGIN_LOOKUP(hdl, n) dlsym(hdl, n)
  #define PLUGIN_INIT()         PLUGIN_LOAD(0)
  #define PLUGIN_ERR(hdl)       dlerror()
  #define PLUGIN_CLOSE(hdl)     dlclose(hdl)
#endif

#endif // PLUGINWAPPER_H
