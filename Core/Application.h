#ifndef VL_APPLICATION_H
#define VL_APPLICATION_H
#include <memory>

namespace vl::Platform {
class Window;
}
namespace vl {
class Core;
}

namespace vl::App {
class Application{
public:
    int Run();
private:
    std::unique_ptr<vl::Platform::Window> window_;
	std::unique_ptr<vl::Core> core_;
};
}


#endif // VL_APPLICATION_H
