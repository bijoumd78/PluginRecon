#include "pluginmanager.h"
#include <string>
#include <map>
#include <set>

#if _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

namespace pluginrecon {

    class PluginInstance::Impl
    {
    public:
        std::string mFileName;
        std::string mDisplayName;

#if _WIN32
        // Plugin loading routines for Windows
        HINSTANCE handle;

        using PluginFunc = FARPROC;

        bool Load()
        {
            handle = LoadLibrary(mFileName.c_str());
            return (handle != nullptr);
        }

        bool Unload()
        {
            if (!handle)
                return true;
            return FreeLibrary(handle) != 0;
        }

        PluginFunc GetFunction(const std::string& name)
        {
            PluginFunc fptr = GetProcAddress(handle, name.c_str());
            if (!fptr)
                return nullptr;
            return fptr;
        }
#else
        // Plugin loading routines for Mac & Linux
        void* handle;

        typedef void(*PluginFunc)();

        bool Load()
        {
            handle = dlopen(mFileName.c_str(), RTLD_LOCAL | RTLD_LAZY);
            return (handle != NULL);
        }

        bool Unload()
        {
            if (!handle)
                return true;
            return dlclose(handle) == 0;
        }

        PluginFunc GetFunction(const std::string& name)
        {
            dlerror();
            PluginFunc fptr = (PluginFunc)dlsym(handle, name.c_str());
            if (dlerror())
                return NULL;
            return fptr;
        }
#endif


    };

    PluginInstance::PluginInstance(const std::string& name) :
        mImpl(std::make_shared<Impl>())
    {
        mImpl->mDisplayName = name;

#if _WIN32
        mImpl->mFileName = name + ".dll";
#elif __APPLE__
        mImpl->mFileName = "lib" + name + ".dylib";
#else
        mImpl->mFileName = "lib" + name + ".so";
#endif
    }

    bool PluginInstance::Load()const
    {
        if (!mImpl->Load())
            return false;

        auto init_func = mImpl->GetFunction("PluginInit");
        if (!init_func)
            return false;

        // Initialize loaded plugins
        (*init_func)();

        if (auto name_string = mImpl->GetFunction("PluginDisplayName"); name_string)
        {
            auto ptr = (const char**)name_string;
            mImpl->mDisplayName = *ptr;
        }

        return true;
    }

    bool PluginInstance::Unload() const
    {
        return mImpl->Unload();
    }

    bool PluginInstance::IsLoaded() const
    {
        return (mImpl->handle != nullptr);
    }

    std::string PluginInstance::GetFileName() const
    {
        return mImpl->mFileName;
    }

    std::string PluginInstance::GetDisplayName() const
    {
        return mImpl->mDisplayName;
    }

    PluginManager& PluginManager::GetInstance()
    {
        static PluginManager mgr;
        return mgr;
    }

    bool PluginManager::LoadAll()
    {
        // hardcode loading our 2 example plugins
        // in reality, this would search for all plugins to load
        Load("worker1");
        Load("worker2");
        return true;
    }

    bool PluginManager::Load(const std::string& name)
    {
        // have we already loaded this plugin?
        static std::set<std::string, std::less<>> loaded;
        if (loaded.find(name) != loaded.end())
            return true;

        // try to load this plugin
        auto pi = std::make_shared<PluginInstance>(name);
        if (!pi->Load())
        {
            pi.reset();
        }

        // success! add the plugin to our manager
        mPlugins.push_back(pi);

        // and don't try to load it again
        loaded.insert(name);
        return true;
    }

    bool PluginManager::UnloadAll() const
    {
        // not implemented yet
        return false;
    }

    bool PluginManager::Unload(const std::string& name) const
    {
        (void)name;
        // not implemented yet
        return false;
    }

    std::vector<std::shared_ptr<PluginInstance>> PluginManager::GetAllPlugins()
    {
        // If we had an external metadata file that described all of the
        // plugins, this would be the point where we load that file -
        // without loading the actual plugins.  Without that external
        // metadata, we need to load all plugins.
        LoadAll();
        return mPlugins;
    }
}
