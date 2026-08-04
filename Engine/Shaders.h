#pragma once

#include <DirectXMath.h>
#include <wrl/client.h>

#include <d3d11.h>

class Graphics;

struct Vertex {
    float position[3];
    float textureCoordinates[2];
};

struct Transform {
    DirectX::XMMATRIX world;
    DirectX::XMMATRIX view;
    DirectX::XMMATRIX projection;
};

class Shader final {
public:
    explicit Shader(const Graphics& graphics);

    [[nodiscard]] ID3D11Buffer* GetVertexBuffer() const { return vertexBuffer_.Get(); }
    [[nodiscard]] ID3D11Buffer* GetIndexBuffer() const { return indexBuffer_.Get(); }
    [[nodiscard]] ID3D11Buffer* GetTransformBuffer() const { return transformBuffer_.Get(); }
    [[nodiscard]] ID3D11InputLayout* GetInputLayout() const { return inputLayout_.Get(); }
    [[nodiscard]] ID3D11VertexShader* GetVertexShader() const { return vertexShader_.Get(); }
    [[nodiscard]] ID3D11PixelShader* GetPixelShader() const { return pixelShader_.Get(); }

private:
    void CreateShaders();
    void CreateGeometry();

    const Graphics& graphics_;
    Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout_;
    Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader_;
    Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader_;
    Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer_;
    Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer_;
    Microsoft::WRL::ComPtr<ID3D11Buffer> transformBuffer_;
};
