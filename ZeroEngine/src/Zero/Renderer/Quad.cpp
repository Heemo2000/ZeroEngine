#include "zeropch.h"
#include "Quad.h"


namespace Zero
{
	Quad::Quad(std::vector<MeshVertex> vertices) : m_Vertices(vertices)
	{

	}
	void Quad::SetVertexPosition(glm::vec3 position, uint32_t index)
	{
		ZERO_ASSERT(index >= 4 || index <= 0, "Invalid vertex index!!")
		m_Vertices[index].Position = position;
		
	}
}