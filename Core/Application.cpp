#include "Application.h"
#include "Platform/Windows/vlWindow.h"
#include "vlCore.h"
#include <iostream>

vl::App::Application::Application() = default;
vl::App::Application::~Application() = default;

int vl::App::Application::Run() {
    constexpr unsigned int width = 1280;
    constexpr unsigned int height = 720;
    window_ = std::make_unique<vl::Platform::Window>();
    if (!window_->vlCreateWindow(width, height, "Vanilla Engine")) {
        return 1;
    }
    core_ = std::make_unique<vl::Core>();
    core_->VlInitialize(*window_);
    
   while (!glfwWindowShouldClose(window_->GetHandle())) {
       glfwPollEvents();
           
    }

   glfwTerminate();
   return 0;
}
