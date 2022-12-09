#include "zeropch.h"
#include "InstanceManager.h"
#include <Zero/Renderer/Renderer.h>
#include <glad/glad.h>


namespace Zero
{

	InstanceManager::InstanceManager(std::vector<float> vertices, std::vector<uint32_t> indices, uint32_t instanceCount) : m_InstanceCount(instanceCount)
	{
		BufferLayout quadLayout =
		{
			{"a_Position",ShaderDataType::Float3}
		};

		m_VertexArray = Zero::VertexArray::Create();

		m_VertexBuffer.reset(Zero::VertexBuffer::Create(vertices.data(), vertices.size() * sizeof(float)));
		m_VertexBuffer->SetLayout(quadLayout);

		m_IndexBuffer.reset(Zero::IndexBuffer::Create(indices.data(), indices.size()));

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		std::string instanceVS = R"(
			#version 460 core
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_TransformationMatrix;
			uniform vec3 offsets[30*30];			

			vec4 cachedPos = vec4(0.0,0.0,0.0,1.0);
			
			void calculatePosition(in mat4 viewProjection,in mat4 transformationMatrix,in vec3 vertexPosition,in vec3 offset,out vec4 result)
			{
				result = viewProjection * transformationMatrix * vec4(vertexPosition + offset,1.0);
			}

		    void main()
			{	
				calculatePosition(u_ViewProjection,u_TransformationMatrix,a_Position,offsets[gl_InstanceID],cachedPos);
				gl_Position = cachedPos;
			}
		)";


		std::string instanceFS = R"(
			#version 460 core
			
			uniform vec4 u_Color;
			out vec4 outColor;
			void main()
			{
				outColor = u_Color;
			}
	)";

		m_ShaderLibrary.reset(new Zero::ShaderLibrary());
		
		std::string filePath = "src/shaders/instance.glsl";
		auto shader = m_ShaderLibrary->Load(filePath);
		shader->Bind();
	}

	void InstanceManager::SetOrigin(glm::vec3 position)
	{
		m_Transform.SetPosition(position);
	}

	void InstanceManager::SetOffset(uint32_t instanceNo, glm::vec3 offset)
	{
		
		if (instanceNo > m_InstanceCount)
		{
			return;
		}
		auto shader = m_ShaderLibrary->Get("instance");
		shader->UploadData("offsets[" + std::to_string(instanceNo) + "]", offset);
	}

	void InstanceManager::SetScale(glm::vec3 scale)
	{
		m_Transform.SetScale(scale);
	}

	void InstanceManager::SetColor(glm::vec4 color)
	{
		auto shader = m_ShaderLibrary->Get("instance");
		shader->Bind();
		shader->UploadData("u_Color", color);
	}

	void InstanceManager::DrawInstances()
	{
		auto shader = m_ShaderLibrary->Get("instance");
		Zero::Renderer::Submit(shader, m_VertexArray, m_Transform.GetTransformationMatrix(), m_InstanceCount);
	}

}
