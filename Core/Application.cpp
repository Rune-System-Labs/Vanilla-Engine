#include "Application.h"
#include "Platform/Windows/vlWindow.h"
#include "Platform/Windows/vlRenderer.h"
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
	renderer_ = std::make_unique<vl::Platform::Renderer>();

	renderer_->InitRenderer(core_->GetDevice(), core_->GetRenderTargetView(), core_->GetContext(), core_->GetSwapChain());
	renderer_->vlViewport(width, height);

   while (!glfwWindowShouldClose(window_->GetHandle())) {
       glfwPollEvents();
       
	   renderer_->ClearScreen();

	   renderer_->Present();
    }
   return 0;
}
