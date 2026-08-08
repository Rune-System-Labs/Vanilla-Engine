#include "Application.h"
#include "Platform/Windows/vlWindow.h"
#include "Platform/Windows/vlRenderer.h"
#include "Platform/Windows/vlUserInterface.h"
#include "Platform/DirectX/VertexShader.h"
#include "Platform/DirectX/PixelShader.h"
#include "vlCore.h"
#include <iostream>
#include <algorithm>

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
	userInterface_ = std::make_unique<vl::UI::UserInterface>();
	vertexShader_ = std::make_unique<vl::core::Shaders::VertexShader>();
	pixelShader_ = std::make_unique<vl::core::Shaders::PixelShader>();

	vertexShader_->InitInstance(core_->GetDevice());
	vertexShader_->vlInitVShader();

	pixelShader_->InitInstance(core_->GetDevice());
	pixelShader_->vlInitPShader();

	userInterface_->vlInitUI(window_->GetHandle(), core_->GetDevice(), core_->GetContext());
    userInterface_->RegisterSettingsCallback(std::bind(&vl::Platform::Renderer::vlGenRenderState, renderer_.get()));

	renderer_->InitRenderer(core_->GetDevice(), core_->GetRenderTargetView(), core_->GetContext(), core_->GetSwapChain());
	renderer_->vlViewport(width, height);

	while (!glfwWindowShouldClose(window_->GetHandle())) {
       glfwPollEvents();
       
	   renderer_->ClearScreen();
	   userInterface_->vlStageUI();
	   renderer_->vlStageRenderer();
	   userInterface_->vlRenderUI();

	   renderer_->Present();
    }
   return 0;
}
