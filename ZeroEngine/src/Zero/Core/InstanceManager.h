#pragma once
#include <Zero/Renderer/Buffer.h>
#include <Zero/Renderer/VertexArray.h>
#include <Zero/Renderer/Shader.h>
#include <Zero/Core/Transform.h>
#include <glm/glm.hpp>
#include <vector>

namespace Zero
{
class InstanceManager
{
public:
	InstanceManager(std::vector<float> vertices,std::vector<uint32_t> indices,uint32_t instanceCount);
	void SetOrigin(glm::vec3 position);
	void SetOffset(uint32_t instanceNo, glm::vec3 position);
	void SetScale(glm::vec3 scale);
	void SetColor(glm::vec4 color);
	void DrawInstances();
private:
	uint32_t m_InstanceCount;
	Zero::Ref<Zero::VertexArray> m_VertexArray;
	Zero::Ref<Zero::VertexBuffer> m_VertexBuffer;
	Zero::Ref<Zero::IndexBuffer> m_IndexBuffer;
	Zero::Ref<Zero::Shader> m_Shader;

	Zero::Transform m_Transform = Zero::Transform(glm::vec3(0.0f, 0.0f, 0.0f));
};
}
