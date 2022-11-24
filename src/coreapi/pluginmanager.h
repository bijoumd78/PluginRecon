#pragma once

#include "defines.h"
#include <string>
#include <vector>
#include <memory>
#include <set>

namespace pluginrecon {

    ///
    /// An object to represent a single plugin in the system
    ///
    class CORE_API PluginInstance final
    {
    public:
        explicit PluginInstance(const std::string& name);

        // Make this object be noncopyable as it holds a pointer
        PluginInstance(const PluginInstance&) = delete;
        const PluginInstance& operator =(const PluginInstance&) = delete;

        /// Load the plugin
        bool Load()const;
        /// Unload the plugin
        bool Unload() const;
        /// Return true if the plugin is loaded
        bool IsLoaded() const;

        /// Return the path to the plugin file on disk
        std::string GetFileName()const;
        /// Return the display name for the plugin
        std::string GetDisplayName()const;

    private:
        class Impl;
        std::shared_ptr<Impl> mImpl;
    };

    ///
    /// A manger for all plugins in the Core API
    ///
    class CORE_API PluginManager
    {
    public:
        /// Return the single instance of the plugin manager
        static PluginManager& GetInstance();

        /// Load all plugins
        bool LoadAll();
        /// Load a single named plugin
        bool Load(const std::string& name);

        /// Unload all plugins
        bool UnloadAll() const;
        /// Unload a single named plugin
        bool Unload(const std::string& name) const;

        /// Return a list of all plugins
        std::vector<std::shared_ptr<PluginInstance>> GetAllPlugins();

    private:
        PluginManager() = default;
        ~PluginManager() = default;
        PluginManager(const PluginManager&) = delete;
        const PluginManager& operator =(const PluginManager&) = delete;

        std::vector<std::shared_ptr<PluginInstance>> mPlugins;
        static std::set<std::string, std::less<>> loaded;
    };

}
