#ifndef VL_MESH_H
#define VL_MESH_H
#include <d3d11.h>
#include <wrl/client.h>
#include <iostream>
#include <memory>
using namespace Microsoft::WRL;

namespace vl::Resource {
	class Buffer;
}

struct Vertex {
	float Position[3];
	float Texcoord[2];
};

namespace vl::Mesh {
	class Mesh {
	public:
		Mesh();
		~Mesh();
		void vlInitMesh(ComPtr<ID3D11Device>Device_, ComPtr<ID3D11DeviceContext>context);
		void vlDrawMesh();
	private:
		UINT vertexCount = 0;
		UINT indexCount = 0;
		std::unique_ptr<vl::Resource::Buffer>Buffer_;
		ComPtr<ID3D11Buffer>vertexBuffer;
		ComPtr<ID3D11Buffer>indexBuffer;
		ComPtr<ID3D11DeviceContext>context;
	};
}



#endif // VL_MESH_H
