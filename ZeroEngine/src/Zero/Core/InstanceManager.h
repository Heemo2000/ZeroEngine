#pragma once
#include <Zero/Renderer/Buffer.h>
#include <Zero/Renderer/VertexArray.h>
#include <Zero/Renderer/Shader.h>
#include <Zero/Core/Transform.h>
#include <glm/glm.hpp>


namespace Zero
{
class InstanceManager
{
public:
	InstanceManager(float* vertices,unsigned int* indices,uint32_t instanceCount);
	void SetOrigin(glm::vec3 position);
	void SetPosition(uint32_t instanceNo, glm::vec3 position);
	void DrawInstances();
private:
	uint32_t m_InstanceCount;
	Zero::Ref<Zero::VertexArray> m_MainVA;
	Zero::Ref<Zero::VertexBuffer> m_ActualModelVB;
	Zero::Ref<Zero::IndexBuffer> m_ActualModelIB;
	Zero::Ref<Zero::Shader> m_Shader;

	Zero::Ref<Zero::VertexBuffer> m_InstanceVB;
	Zero::Transform m_Transform = Zero::Transform(glm::vec3(0.0f, 0.0f, 0.0f));
	glm::vec3 m_Translations[20 * 20];
};
}
