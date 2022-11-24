#include "coreapi.h"
#include "pluginapi.h"

namespace pluginrecon {

    void RegisterRenderer(const char* type, const RendererInitFunc& init_cb, const RendererFreeFunc& free_cb)
    {
        RendererFactory::RegisterRenderer(type, init_cb);
        (void)free_cb; // we never free these objects
    }

}

