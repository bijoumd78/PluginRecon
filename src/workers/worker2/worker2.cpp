#include "pluginapi.h"
//#include <logger.h>
#include <iostream>


namespace pluginrecon {

    class DirectXRenderer : public IRenderer
    {
    public:
        bool LoadScene(const char* filename) final { (void)filename; return true; }
        void SetViewportSize(int w, int h) final { (void)w; (void)h; }
        void SetCameraPos(double x, double y, double z) final { (void)x; (void)y; (void)z; }
        void SetLookAt(double x, double y, double z) final { (void)x; (void)y; (void)z; }
        void Render() final { /*Logger::info("DirectX Render");*/ std::cout << "DirectX Render" << std::endl; }
    };

    PLUGIN_FUNC IRenderer* CreateRenderer()
    {
        return new DirectXRenderer;
    }

    PLUGIN_FUNC void DestroyRenderer(IRenderer* r)
    {
        delete r;
        r = nullptr;
    }

    PLUGIN_DISPLAY_NAME("DirectX Renderer");

    PLUGIN_INIT()
    {
        // Load logging configuration file
        //Logger log("logConfig.json", "Plugin2");

        // register our new renderer
        //Logger::info( "PLUGIN_INIT");
        std::cout << "PLUGIN_INIT" << std::endl;
        RegisterRenderer("directx", CreateRenderer, DestroyRenderer);
        return 0;
    }
}
