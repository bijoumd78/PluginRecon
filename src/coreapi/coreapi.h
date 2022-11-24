#pragma once

#include "defines.h"
#include "renderer.h"

#include <functional>
#include <string>
#include <map>

namespace pluginrecon {

    ///
    /// A factory object in the Core API
    ///
    class CORE_API RendererFactory
    {
    public:
        using CreateCallback = std::function<IRenderer* ()>;

        static void RegisterRenderer(const std::string& type, const CreateCallback& cb);

        static void UnregisterRenderer(const std::string& type);

        static IRenderer* CreateRenderer(const std::string& type);

    private:
        using CallbackMap = std::map<std::string, CreateCallback, std::less<>>;
        static CallbackMap mRenderers;
    };

}
