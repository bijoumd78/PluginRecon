#include "coreapi.h"
#include "pluginmanager.h"
#include <logger.h>
#include <memory>
#include <iostream>

///
/// A Mesa-based software renderer
///
class MesaRenderer : public pluginrecon::IRenderer
{
public:
    bool LoadScene(const char* filename) final { (void)filename; return true; }
    void SetViewportSize(int w, int h) final { (void)w; (void)h; }
    void SetCameraPos(double x, double y, double z) final { (void)x; (void)y; (void)z; }
    void SetLookAt(double x, double y, double z) final { (void)x; (void)y; (void)z; }
    void Render() final { /*pluginrecon::Logger::info("Mesa Render");*/ std::cout << "Mesa Render" << std::endl; }
    static IRenderer* Create() { return new MesaRenderer; }
};

int main()
{
    using namespace pluginrecon;
    // Load logging configuration file
    Logger log("logConfig.json", "CoreAPI");

    // create the factory object
    RendererFactory::RegisterRenderer("mesa", MesaRenderer::Create);

    // print the pretty name of all available plugins
    auto plugins = PluginManager::GetInstance().GetAllPlugins();

#if 0
    std::vector<PluginInstance *>::iterator it;
    for (it = plugins.begin(); it != plugins.end(); ++it)
#endif

    for(const auto& p : plugins)
    {
        std::cout << "Plugin: " << p->GetDisplayName() << std::endl;
        //Logger::info("Plugin: {}", p->GetDisplayName());
    }

    // load all plugins
    PluginManager::GetInstance().LoadAll();

    // create a Mesa software renderer (added by this module)
    auto mesa = RendererFactory::CreateRenderer("mesa");
    if (!mesa)
    {
        std::cout << "Failed to register 'mesa' renderer!" << std::endl;
        //Logger::error("Failed to register 'mesa' renderer!");
        return 1;
    }

    mesa->Render();
    delete mesa;

    // create an OpenGL renderer (added by a plugin)
    auto ogl = RendererFactory::CreateRenderer("opengl");
    if (!ogl)
    {
        std::cout << "Failed to load 'opengl' plugin!" << std::endl;
        //Logger::error("Failed to load 'opengl' plugin!");
        return 1;
    }

    ogl->Render();
    delete ogl;

    return 0;
}
