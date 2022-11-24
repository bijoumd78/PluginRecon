#include "coreapi.h"
#include <iostream>

namespace pluginrecon {

    // instantiate the static variable in RendererFactory
    RendererFactory::CallbackMap RendererFactory::mRenderers;

    void RendererFactory::RegisterRenderer(const std::string& type, const CreateCallback& cb)
    {
        mRenderers[type] = cb;
    }

    void RendererFactory::UnregisterRenderer(const std::string& type)
    {
        mRenderers.erase(type);
    }

    IRenderer* RendererFactory::CreateRenderer(const std::string& type)
    {
        if (auto it = mRenderers.find(type); it != mRenderers.end())
        {
            // call the creation callback to construct this derived type
            return (it->second)();
        }

        return nullptr;
    }

}
