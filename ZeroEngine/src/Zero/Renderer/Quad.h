#pragma once
#include <glm/glm.hpp>

namespace Zero
{
	struct MeshVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
	};

	class Quad
	{
	public:
		Quad(std::vector<MeshVertex> vertices);
		inline std::vector<MeshVertex> GetVertices() const { return m_Vertices; };
		void SetVertexPosition(glm::vec3 position, uint32_t index);
	private:
		std::vector<MeshVertex> m_Vertices;
		std::vector<uint32_t> m_Indices;
	};
}


