#include "VertexShader.h"
#include <fstream>
#include <iostream>
#include <string_view>
#include <vector>
#include "PixelShader.h"

namespace vl::Core {
	VertexShader::VertexShader(){

	}

	VertexShader::~VertexShader()
	{
	}


	void VertexShader::CompileVertexShader(std::string_view filePath, const char* entryPoint, const char* shaderModel) {
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
			VertexShaderByteCode.GetAddressOf(),
			errorBlob.GetAddressOf());

		vlGenInputLayout(VertexShaderByteCode.Get(), VertexShaderByteCode->GetBufferSize());
	}

	void VertexShader::vlGenInputLayout(ComPtr<ID3DBlob> VertexShaderByteCode, UINT bytecodeShaderLength) {
		ComPtr<ID3D11ShaderReflection> shaderReflection = ComPtr<ID3D11ShaderReflection>();
		D3DReflect(VertexShaderByteCode.Get(), VertexShaderByteCode->GetBufferSize(), IID_PPV_ARGS(shaderReflection.GetAddressOf()));

		D3D11_SHADER_DESC shaderDesc = {};
		shaderReflection->GetDesc(&shaderDesc);

		std::vector<D3D11_INPUT_ELEMENT_DESC> inputParams;
		inputParams.reserve(shaderDesc.InputParameters);

		for (UINT i = 0; i < shaderDesc.InputParameters; ++i) {
			D3D11_SIGNATURE_PARAMETER_DESC ParamDesc = {};
			shaderReflection->GetInputParameterDesc(i, &ParamDesc);

			D3D11_INPUT_ELEMENT_DESC Layout = {};
			Layout.SemanticIndex = ParamDesc.SemanticIndex;
			Layout.SemanticName = ParamDesc.SemanticName;
			Layout.InputSlot = 0;
			Layout.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			Layout.InstanceDataStepRate = 0;
			Layout.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

			switch (ParamDesc.Mask) {
			case 1:Layout.Format = DXGI_FORMAT_R32G32_FLOAT;
				break;
			case 3:Layout.Format = DXGI_FORMAT_R32G32_FLOAT;
				break;
			case 7:Layout.Format = DXGI_FORMAT_R32G32B32_FLOAT;
				break;
			case 15:Layout.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
				break;
			}

			inputParams.push_back(Layout);
		}

		device->CreateInputLayout(
			inputParams.data(),
			(UINT)inputParams.size(),
			VertexShaderByteCode->GetBufferPointer(),
			VertexShaderByteCode->GetBufferSize(),
			inputLayout.GetAddressOf()
		);
	}

	void VertexShader::InitInstance(ComPtr<ID3D11Device> deviceInstance){
		device = deviceInstance;
	}
}