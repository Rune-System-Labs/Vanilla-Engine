#include "Renderer.h"

#include "Graphics.h"
#include "Shaders.h"
#include "Texture.h"

#include <GLFW/glfw3.h>
#include <cstring>

Renderer::Renderer(const Graphics& graphics, const Shader& shader, const Texture& texture)
    : graphics_(graphics), shader_(shader), texture_(texture) {
}

void Renderer::ClearScreen(const float red, const float green, const float blue) const {
    const float color[] = { red, green, blue, 1.0f };
    graphics_.GetContext()->ClearRenderTargetView(graphics_.GetRenderTargetView(), color);
    graphics_.GetContext()->ClearDepthStencilView(graphics_.GetDepthStencilView(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Renderer::RenderEntity() {
    const UINT stride = sizeof(Vertex);
    const UINT offset = 0;
    ID3D11Buffer* vertexBuffer = shader_.GetVertexBuffer();
    graphics_.GetContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
    graphics_.GetContext()->IASetIndexBuffer(shader_.GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
    graphics_.GetContext()->IASetInputLayout(shader_.GetInputLayout());
    graphics_.GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    graphics_.GetContext()->VSSetShader(shader_.GetVertexShader(), nullptr, 0);
    graphics_.GetContext()->PSSetShader(shader_.GetPixelShader(), nullptr, 0);

    ID3D11Buffer* transformBuffer = shader_.GetTransformBuffer();
    graphics_.GetContext()->VSSetConstantBuffers(0, 1, &transformBuffer);
    ID3D11ShaderResourceView* texture = texture_.GetShaderResourceView();
    ID3D11SamplerState* sampler = texture_.GetSamplerState();
    graphics_.GetContext()->PSSetShaderResources(0, 1, &texture);
    graphics_.GetContext()->PSSetSamplers(0, 1, &sampler);

    UpdateTransforms();
    graphics_.GetContext()->DrawIndexed(36, 0, 0);
}

void Renderer::UpdateTransforms() {
    constexpr float cameraSpeed = 0.01f;
    rotation_ += 0.01f;

    GLFWwindow* window = graphics_.GetWindow();
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera_.Move(0.0f, 0.0f, cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera_.Move(0.0f, 0.0f, -cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera_.Move(-cameraSpeed, 0.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera_.Move(cameraSpeed, 0.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) camera_.Move(0.0f, cameraSpeed, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) camera_.Move(0.0f, -cameraSpeed, 0.0f);
    const DirectX::XMMATRIX world = DirectX::XMMatrixRotationRollPitchYaw(rotation_, rotation_, 0.0f);
    const DirectX::XMMATRIX view = camera_.GetViewMatrix();
    const DirectX::XMMATRIX projection = DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV2, graphics_.AspectRatio(), 0.1f, 100.0f);
    const Transform transforms{ DirectX::XMMatrixTranspose(world), DirectX::XMMatrixTranspose(view), DirectX::XMMatrixTranspose(projection) };

    D3D11_MAPPED_SUBRESOURCE mapped{};
    if (SUCCEEDED(graphics_.GetContext()->Map(shader_.GetTransformBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped))) {
        std::memcpy(mapped.pData, &transforms, sizeof(transforms));
        graphics_.GetContext()->Unmap(shader_.GetTransformBuffer(), 0);
    }
}

void Renderer::Present() const {
    graphics_.GetSwapChain()->Present(1, 0);
}
