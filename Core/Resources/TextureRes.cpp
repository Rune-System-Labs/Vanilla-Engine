#include "TextureRes.h"

namespace vl::Resources {
	ComPtr<ID3D11ShaderResourceView> Texture::vlLoadDDS(ComPtr<ID3D11ShaderResourceView>& srv, ComPtr<ID3D11Device>& device, const wchar_t* filename_) {
		DirectX::ScratchImage image;
		DirectX::TexMetadata metadata;
		hr = DirectX::LoadFromDDSFile(filename_, DirectX::DDS_FLAGS_NONE, &metadata, image);
		if (FAILED(hr)) {
			std::cerr << "\aFailed to load DDS file: " << std::endl;
			return;
		}

		DirectX::CreateShaderResourceView(
			device.Get(),
			image.GetImages(),
			image.GetImageCount(),
			metadata,
			srv.GetAddressOf()
		);

		return srv;
	}

	ComPtr<ID3D11ShaderResourceView> Texture::vlLoadWIC(ComPtr<ID3D11ShaderResourceView>& srv, ComPtr<ID3D11Device>& device,const wchar_t* filename_) {
		DirectX::ScratchImage image;
		DirectX::TexMetadata metadata;
		hr = DirectX::LoadFromWICFile(filename_, DirectX::WIC_FLAGS_NONE, nullptr, image);
		if (FAILED(hr)) {
			std::cerr << "\aFailed to load WIC file: " << std::endl;
			return;
		}

		DirectX::CreateShaderResourceView(
			device.Get(),
			image.GetImages(),
			image.GetImageCount(),
			metadata,
			srv.GetAddressOf()
		);

		return srv;
	}
}
