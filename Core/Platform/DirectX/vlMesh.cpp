#include "vlMesh.h"
#include "Core/Resources/Buffer.h"

namespace vl::Mesh {
	Mesh::Mesh()
	{
	}


	Mesh::~Mesh()
	{
	}

	void Mesh::vlInitMesh(ComPtr<ID3D11Device>Device_,ComPtr<ID3D11DeviceContext>context) {
		Buffer_ = std::make_unique<vl::Resource::Buffer>();
		Buffer_->InitDevice(Device_);
		uint32_t Index[] = {
			0, 1, 2, 0, 2, 3,
			4, 6, 5, 4, 7, 6,
			4, 5, 1, 4, 1, 0,
			3, 2, 6, 3, 6, 7,
			1, 5, 6, 1, 6, 2,
			4, 0, 3, 4, 3, 7
		};

		Buffer_->vlGenBuffers<uint32_t>(D3D11_USAGE_DEFAULT, Index,D3D11_BIND_INDEX_BUFFER ,vertexBuffer);
		indexCount = std::ranges::size(Index);

		Vertex vertices[] = {
			{ { -0.5f,  0.5f, 0.0f },   { 0.0f, 0.0f } },
			{ {  0.5f,  0.5f, 0.0f },   { 1.0f, 0.0f } },
			{ {  0.5f, -0.5f, 0.0f },   { 1.0f, 1.0f } },
			{ { -0.5f, -0.5f, 0.0f },   { 0.0f, 1.0f } }
		};

		Buffer_->vlGenBuffers<Vertex
	}
}

