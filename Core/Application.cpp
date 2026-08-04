#include "Application.h"
#include "Platform/Windows/vlWindow.h"
#include "vlCore.h"
#include <iostream>


int vl::App::Application::Run() {
    constexpr unsigned int width = 1280;
    constexpr unsigned int height = 720;
    window_ = std::make_unique<vl::Platform::Window>();
	core_ = std::make_unique<vl::Core>();
    if (!window_->vlCreateWindow(width, height, "Vanilla Engine")) {
        return 1;
    }
    core_->VlInitialize();
    
   while (!glfwWindowShouldClose(window_->GetHandle())) {
       glfwPollEvents();
           
    }

   glfwTerminate();
   return 0;
}
