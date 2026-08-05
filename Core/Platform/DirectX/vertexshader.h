#ifndef VANNILA_VERTEXSHADER_H
#define VANNILA_VERTEXSHADER_H
#include <d3d11.h>
#include <memory>
#include <wrl/client.h>
#include <string>
#include <d3dcompiler.h>
using Microsoft::WRL::ComPtr;

namespace vl::Core {
	class VertexShader {
	public:
		VertexShader();
		~VertexShader();
		void CompileVertexShader(std::string_view filePath, const char* entryPoint, const char* shaderModel);
		void InitInstance(ComPtr<ID3D11Device>deviceInstance);
		[[nodiscard]] ID3D11VertexShader* GetVertexShader() const { return vertexShader.Get(); }
		[[nodiscard]] ID3D11InputLayout* GetLayout() const { return inputLayout.Get(); }
		[[nodiscard]] ID3DBlob* GetVertexShaderByteCode() const { return VertexShaderByteCode.Get(); }
	private:
		void vlGenInputLayout(ComPtr<ID3DBlob> VertexShaderByteCode,UINT bytecodeShaderLength);
		ComPtr<ID3D11VertexShader> vertexShader = nullptr;
		ComPtr<ID3DBlob> VertexShaderByteCode = nullptr;
		ComPtr<ID3DBlob> errorBlob = nullptr;
		ComPtr<ID3D11InputLayout> inputLayout = nullptr;
		ComPtr<ID3D11Device> device;
	};
}

#endif VANNILA_VERTEXSHADER_H
