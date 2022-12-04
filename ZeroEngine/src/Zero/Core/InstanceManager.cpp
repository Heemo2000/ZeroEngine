#include "zeropch.h"
#include "InstanceManager.h"
#include <Zero/Renderer/Renderer.h>
#include <glad/glad.h>


namespace Zero
{
	InstanceManager::InstanceManager(float* vertices, unsigned int* indices, uint32_t instanceCount) : m_InstanceCount(instanceCount)
	{
		BufferLayout layout =
		{
			{"a_Position",ShaderDataType::Float3},
			{"a_Offset",ShaderDataType::Float3}
		};

		m_MainVA.reset(Zero::VertexArray::Create());

		m_ActualModelVB.reset(Zero::VertexBuffer::Create(vertices, sizeof(vertices)));
		m_ActualModelVB->SetLayout(layout);

		m_ActualModelIB.reset(Zero::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_MainVA->AddVertexBuffer(m_ActualModelVB);
		m_MainVA->SetIndexBuffer(m_ActualModelIB);

		m_InstanceVB.reset(Zero::VertexBuffer::Create(&m_Translations[0], sizeof(m_Translations) / sizeof(glm::vec3)));
		m_InstanceVB->SetLayout(layout);
		m_MainVA->AddVertexBuffer(m_InstanceVB);
		glGetError();
		glVertexAttribDivisor(2, 1);

		ZERO_CORE_INFO("Status of vertex attrib divisor : {0}",glGetError());

		std::string quadVS = R"(
			#version 460 core
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec3 a_Offset;
			uniform mat4 u_ViewProjection;
			uniform mat4 u_TransformationMatrix;			

			vec4 cachedPos = vec4(0.0,0.0,0.0,1.0);
			
			void calculatePosition(in mat4 viewProjection,in mat4 transformationMatrix,in vec3 vertexPosition,in vec3 offset,out vec4 result)
			{
				result = viewProjection * transformationMatrix * vec4(vertexPosition + offset,1.0);
			}

		    void main()
			{	
				calculatePosition(u_ViewProjection,u_TransformationMatrix,a_Position,a_Offset,cachedPos);
				gl_Position = cachedPos;
			}
		)";


		std::string quadFS = R"(
			#version 460 core
			
			uniform vec4 u_Color;
			out vec4 outColor;
			void main()
			{
				outColor = u_Color;
			}
	)";

		m_Shader.reset(Zero::Shader::Create(quadVS, quadFS));
	}

	void InstanceManager::SetOrigin(glm::vec3 position)
	{
		m_Transform.SetPosition(position);
	}

	void InstanceManager::SetPosition(uint32_t instanceNo, glm::vec3 position)
	{
		if (instanceNo > m_InstanceCount)
		{
			return;
		}
		ZERO_CORE_INFO("Instance no : {0}", instanceNo);
		m_Translations[instanceNo] = position;
	}

	void InstanceManager::DrawInstances()
	{
		m_Shader->Bind();
		m_Shader->UploadData("u_Color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		Zero::Renderer::Submit(m_Shader, m_MainVA, m_Transform.GetTransformationMatrix(), m_InstanceCount);
	}

}
