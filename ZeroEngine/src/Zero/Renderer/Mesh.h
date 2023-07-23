#pragma once
#include <glm/glm.hpp>
namespace Zero
{
	struct MeshVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
	};

	class Mesh
	{
	public:
		Mesh(std::vector<MeshVertex> vertices, std::vector<uint32_t> indices);
		inline std::vector<MeshVertex> GetVertices() const { return m_Vertices; };
		inline std::vector<uint32_t> GetIndices() const { return m_Indices; };
	private:
		std::vector<MeshVertex> m_Vertices;
		std::vector<uint32_t> m_Indices;
	};
}


