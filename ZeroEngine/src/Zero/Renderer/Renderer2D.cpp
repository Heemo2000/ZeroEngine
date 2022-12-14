#include "zeropch.h"
#include "Renderer2D.h"
#include "Zero/Renderer/Renderer.h"
#include "Zero/Renderer/RenderCommand.h"
#include "Zero/Renderer/VertexArray.h"
#include "Zero/Renderer/Buffer.h"
#include "Zero/Renderer/Shader.h"
#include "Zero/Core/Transform.h"
namespace Zero
{
	
	struct Renderer2DStorage
	{
		Ref<VertexArray> QuadVA;
		Ref<Shader> FlatColorShader;
		Transform QuadTransform = Transform(glm::vec3(0.0f,0.0f,0.0f));
	};

	static Renderer2DStorage* s_Storage;

	void Renderer2D::Init()
	{
		s_Storage = new Renderer2DStorage();
		float quadVertices[] =
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		unsigned int indices[] =
		{
			0,1,2,
			0,2,3
		};

		BufferLayout quadLayout =
		{
			{"a_Position",ShaderDataType::Float3}
		};

		
		s_Storage->QuadVA = Zero::VertexArray::Create();

		Ref<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Zero::VertexBuffer::Create(quadVertices, sizeof(quadVertices)));
		vertexBuffer->SetLayout(quadLayout);

		Ref<IndexBuffer> indexBuffer;
		indexBuffer.reset(Zero::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		s_Storage->QuadVA->AddVertexBuffer(vertexBuffer);
		s_Storage->QuadVA->SetIndexBuffer(indexBuffer);

		s_Storage->FlatColorShader = Shader::Create("src/shaders/quad.glsl");
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Storage->FlatColorShader->Bind();
		s_Storage->FlatColorShader->UploadData("u_TransformationMatrix",glm::mat4(1.0f));
		s_Storage->FlatColorShader->UploadData("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::Shutdown()
	{
		delete s_Storage;
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& scale, const glm::vec4& color)
	{
		DrawQuad({position.x,position.y,0.0f}, {scale.x,scale.y,0.0f}, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec3& scale, const glm::vec4& color)
	{
		s_Storage->QuadTransform.SetPosition(position);
		s_Storage->QuadTransform.SetScale(scale);
		s_Storage->FlatColorShader->Bind();
		s_Storage->FlatColorShader->UploadData("u_Color", color);
		s_Storage->FlatColorShader->UploadData("u_TransformationMatrix", s_Storage->QuadTransform.GetTransformationMatrix());
		s_Storage->QuadVA->Bind();
		RenderCommand::DrawIndexed(s_Storage->QuadVA);
	}

}

