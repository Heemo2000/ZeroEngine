#include "zeropch.h"
#include "Mesh.h"


namespace Zero
{
	Mesh::Mesh(std::vector<MeshVertex> vertices, std::vector<uint32_t> indices) : m_Vertices(vertices), m_Indices(indices)
	{

	}
}