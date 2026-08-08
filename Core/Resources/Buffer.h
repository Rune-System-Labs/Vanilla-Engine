#ifndef BUFFER_H
#define BUFFER_H
#include <algorithm>
#include <d3d11.h>
#include <iostream>
#include <wrl/client.h>
#include <span>
using Microsoft::WRL::ComPtr;

namespace vl::Resource {	
class Buffer {
public:
Buffer();
~Buffer() {
std::cout << "VL::Buffer resources released!" << std::endl;
}
void InitDevice(ComPtr<ID3D11Device> deviceInstance);
template<typename T>
void vlGenBuffers(D3D11_USAGE Usage,std::span<T> data,UINT bindFlags, ComPtr<ID3D11Buffer>& buffers);
private:
ComPtr<ID3D11Device> device;
HRESULT hr = S_OK;
};
template<typename T>
inline void vl::Resource::Buffer::vlGenBuffers(D3D11_USAGE Usage, std::span<T> data, UINT bindFlags, ComPtr<ID3D11Buffer>& buffers){
		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.Usage = Usage;
		bufferDesc.ByteWidth = static_cast<UINT>(data.size() * sizeof(T));
		bufferDesc.BindFlags = bindFlags;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = 0;
		D3D11_SUBRESOURCE_DATA initData = {};
		initData.pSysMem = data.data();
		if (initData.pSysMem == nullptr) {
		HRESULT hr = device->CreateBuffer(&bufferDesc, nullptr, buffers.GetAddressOf());
		}
		else {
			hr = device->CreateBuffer(&bufferDesc, &initData, buffers.GetAddressOf());
		}
		if (FAILED(hr)) {
			std::cerr << "Failed to create buffer. HRESULT: " << std::hex << hr << std::endl;
		}
	}
}

#endif // BUFFER_H
