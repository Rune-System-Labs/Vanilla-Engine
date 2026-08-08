#include "PixelShader.h"

namespace vl::core::Shaders {
	PixelShader::PixelShader(){

	}

	void PixelShader::vlInitPShader(){
		CompilePixelShader("Core/Shaders/PixelShader.hlsl", "PSMain", "ps_5_0");
	}

	void PixelShader::CompilePixelShader(std::string_view filePath, const char* entryPoint, const char* shaderModel){
		std::ifstream shaderFile(filePath.data());
		if (!shaderFile.is_open()) {
			std::cerr << "Vannila: Failed to open vertex shader file: " << filePath << std::endl;
			return;
		}

		shaderFile.close();

		HRESULT hr = D3DCompileFromFile(
			std::wstring(filePath.begin(), filePath.end()).c_str(),
			nullptr,
			nullptr,
			entryPoint,
			shaderModel,
			0,
			D3DCOMPILE_SKIP_OPTIMIZATION,
			PixelShaderByteCode.GetAddressOf(),
			errorBlob.GetAddressOf());
	}

	void PixelShader::InitInstance(ComPtr<ID3D11Device> deviceInstance) {
		device = deviceInstance;
	}

	PixelShader::~PixelShader() {

	}
}
