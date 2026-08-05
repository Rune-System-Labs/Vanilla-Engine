#ifndef PIXEL_SHADER_H
#define PIXEL_SHADER_H
#include <d3d11.h>
#include <wrl/client.h>
#include <string_view>
#include <fstream>
#include <iostream>
#include <d3dcompiler.h>
#include <string>
using namespace Microsoft::WRL;

namespace vl::Core {
	class PixelShader {
	public:		
	PixelShader();
	~PixelShader();
	void CompilePixelShader(std::string_view filePath, const char* entryPoint, const char* shaderModel);
	void InitInstance(ComPtr<ID3D11Device>deviceInstance);
	private:
	ComPtr<ID3D11PixelShader> pixelShader_;
	ComPtr<ID3D11Device> device;
	ComPtr<ID3DBlob> PixelShaderByteCode = nullptr;
	ComPtr<ID3DBlob> errorBlob = nullptr;
	};
}


#endif PIXEL_SHADER_H
