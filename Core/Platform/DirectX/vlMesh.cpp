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
		this->context = context;
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

		Buffer_->vlGenBuffers<uint32_t>(D3D11_USAGE_DEFAULT, Index,D3D11_BIND_INDEX_BUFFER ,indexBuffer);
		indexCount = std::ranges::size(Index);

		Vertex vertices[] = {
			{{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
			{{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f}},
			{{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f}},
			{{ 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f}},
			{{-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f}},
			{{-0.5f,  0.5f,  0.5f}, {1.0f, 0.0f}},
			{{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f}},
			{{ 0.5f, -0.5f,  0.5f}, {0.0f, 1.0f}},
		};

		Buffer_->vlGenBuffers<Vertex>(D3D11_USAGE_DEFAULT, vertices, D3D11_BIND_VERTEX_BUFFER, vertexBuffer);
		vertexCount =std::ranges::size(vertices);
	}

	void Mesh::vlDrawMesh() {
		const UINT stride = sizeof(Vertex);
		const UINT offset = 0;
		ID3D11Buffer* vertexBufferPointer = vertexBuffer.Get();
		context->IASetVertexBuffers(0, 1, &vertexBufferPointer, &stride, &offset);
		context->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		context->DrawIndexed(indexCount, 0, 0);
	}
}

