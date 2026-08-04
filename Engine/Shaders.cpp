#include "Shaders.h"

#include "Graphics.h"

#include <array>
#include <d3dcompiler.h>
#include <iterator>
#include <stdexcept>
#include <string>

namespace {
Microsoft::WRL::ComPtr<ID3DBlob> CompileShader(const wchar_t* path, const char* target) {
    Microsoft::WRL::ComPtr<ID3DBlob> bytecode;
    Microsoft::WRL::ComPtr<ID3DBlob> errors;
    const HRESULT result = D3DCompileFromFile(path, nullptr, nullptr, "main", target, D3DCOMPILE_DEBUG, 0,
        &bytecode, &errors);
    if (FAILED(result)) {
        const char* message = errors ? static_cast<const char*>(errors->GetBufferPointer()) : "Unknown compiler error.";
        throw std::runtime_error(std::string("Shader compilation failed: ") + message);
    }
    return bytecode;
}
}

Shader::Shader(const Graphics& graphics) : graphics_(graphics) {
    CreateShaders();
    CreateGeometry();
}

void Shader::CreateShaders() {
    const auto vertexBytecode = CompileShader(L"VS.hlsl", "vs_5_0");
    const auto pixelBytecode = CompileShader(L"PS.hlsl", "ps_5_0");

    if (FAILED(graphics_.GetDevice()->CreateVertexShader(vertexBytecode->GetBufferPointer(), vertexBytecode->GetBufferSize(), nullptr, &vertexShader_)) ||
        FAILED(graphics_.GetDevice()->CreatePixelShader(pixelBytecode->GetBufferPointer(), pixelBytecode->GetBufferSize(), nullptr, &pixelShader_))) {
        throw std::runtime_error("Could not create a Direct3D shader.");
    }

    const D3D11_INPUT_ELEMENT_DESC layout[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    if (FAILED(graphics_.GetDevice()->CreateInputLayout(layout, static_cast<UINT>(std::size(layout)),
        vertexBytecode->GetBufferPointer(), vertexBytecode->GetBufferSize(), &inputLayout_))) {
        throw std::runtime_error("Could not create the vertex layout.");
    }
}

void Shader::CreateGeometry() {
    constexpr std::array<Vertex, 8> vertices = {{
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}}, {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f}}, {{ 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f}},
        {{-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f}}, {{-0.5f,  0.5f,  0.5f}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f}}, {{ 0.5f, -0.5f,  0.5f}, {0.0f, 1.0f}},
    }};
    constexpr std::array<std::uint32_t, 36> indices = { 0,1,2, 0,2,3, 4,6,5, 4,7,6, 4,5,1, 4,1,0, 3,2,6, 3,6,7, 1,5,6, 1,6,2, 4,0,3, 4,3,7 };

    D3D11_BUFFER_DESC vertexDescription{};
    vertexDescription.ByteWidth = static_cast<UINT>(sizeof(vertices));
    vertexDescription.Usage = D3D11_USAGE_DEFAULT;
    vertexDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    D3D11_SUBRESOURCE_DATA vertexData{};
    vertexData.pSysMem = vertices.data();

    D3D11_BUFFER_DESC indexDescription{};
    indexDescription.ByteWidth = static_cast<UINT>(sizeof(indices));
    indexDescription.Usage = D3D11_USAGE_DEFAULT;
    indexDescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
    D3D11_SUBRESOURCE_DATA indexData{};
    indexData.pSysMem = indices.data();

    D3D11_BUFFER_DESC transformDescription{};
    transformDescription.ByteWidth = sizeof(Transform);
    transformDescription.Usage = D3D11_USAGE_DYNAMIC;
    transformDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    transformDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    if (FAILED(graphics_.GetDevice()->CreateBuffer(&vertexDescription, &vertexData, &vertexBuffer_)) ||
        FAILED(graphics_.GetDevice()->CreateBuffer(&indexDescription, &indexData, &indexBuffer_)) ||
        FAILED(graphics_.GetDevice()->CreateBuffer(&transformDescription, nullptr, &transformBuffer_))) {
        throw std::runtime_error("Could not create mesh buffers.");
    }
}
