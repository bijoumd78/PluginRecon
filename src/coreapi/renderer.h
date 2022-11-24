#pragma once

#include <string>

namespace pluginrecon {

    ///
    /// An abstract interface for plugins to create new renderers.
    ///
    class IRenderer
    {
    public:
        virtual ~IRenderer() = default;
        virtual bool LoadScene(const char* filename) = 0;
        virtual void SetViewportSize(int w, int h) = 0;
        virtual void SetCameraPos(double x, double y, double z) = 0;
        virtual void SetLookAt(double x, double y, double z) = 0;
        virtual void Render() = 0;
    };

}
