#ifndef VL_APPLICATION_H
#define VL_APPLICATION_H
#include <memory>

namespace vl::Platform {
class Window;
class Renderer;
}

namespace vl {
class Core;
}

namespace vl::core::Shaders {
	class VertexShader;
	class PixelShader;
}

namespace vl::UI {
class UserInterface;
}

namespace vl::App {
class Application{
public:
    Application();
    ~Application();
    int Run();
private:
	std::unique_ptr<vl::Platform::Window> window_;
	std::unique_ptr<vl::Core> core_;
    std::unique_ptr<vl::Platform::Renderer> renderer_;
	std::unique_ptr<vl::UI::UserInterface> userInterface_;
	std::unique_ptr<vl::core::Shaders::VertexShader> vertexShader_;
	std::unique_ptr<vl::core::Shaders::PixelShader> pixelShader_;
};
}


#endif // VL_APPLICATION_H
