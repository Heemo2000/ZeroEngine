#include "zeropch.h"
#include "Renderer2D.h"
#include "Zero/Renderer/Renderer.h"
#include "Zero/Renderer/RenderCommand.h"
#include "Zero/Renderer/VertexArray.h"
#include "Zero/Renderer/Buffer.h"
#include "Zero/Renderer/Shader.h"
#include "Zero/Core/Transform.h"
#include "Zero/Renderer/Texture.h"
#include "Zero/Renderer/Framebuffer.h"
#include "Zero/Application.h"

namespace Zero
{
	
	
	struct Renderer2DStorage
	{
		static const uint32_t MaxMeshes = 5000;
		static const uint32_t MaxVertices = MaxMeshes * 4;
		static const uint32_t MaxIndices = MaxMeshes * 6;
		static const uint32_t MaxTextureSlots = 32;
		Ref<VertexArray> MeshVA;
		Ref<VertexBuffer> MeshVB;
		Ref<IndexBuffer> MeshIB;
		Ref<Shader> TexturedQuadShader;
		std::array<int, MaxTextureSlots> Samplers;
		std::array<Ref<Texture2D>, MaxTextureSlots> Textures;

		MeshVertex* MeshVerticesBase;
		MeshVertex* MeshVerticesPtr;

		uint32_t MeshIndicesCount = 0;
		uint32_t* MeshIndices;
		
		Ref<Framebuffer> Framebuffer;
	};

	static Renderer2DStorage* s_Storage;

	void Renderer2D::Init()
	{
		s_Storage = new Renderer2DStorage();

		BufferLayout quadLayout =
		{
			{"a_Position",ShaderDataType::Float3},
			{"a_Color",ShaderDataType::Float4},
			{"a_TexCoord", ShaderDataType::Float2},
			{"a_TexIndex", ShaderDataType::Float}
		};

		s_Storage->MeshVerticesBase = new MeshVertex[s_Storage->MaxVertices];
		s_Storage->MeshVerticesPtr = s_Storage->MeshVerticesBase;

		s_Storage->MeshIndices = new uint32_t[s_Storage->MaxIndices];
		uint32_t offset = 0;
		for (int i = 0; i < s_Storage->MaxIndices; i+= 6)
		{
			s_Storage->MeshIndices[i] = offset + 0;
			s_Storage->MeshIndices[i + 1] = offset + 1;
			s_Storage->MeshIndices[i + 2] = offset + 2;

			s_Storage->MeshIndices[i + 3] = offset + 2;
			s_Storage->MeshIndices[i + 4] = offset + 3;
			s_Storage->MeshIndices[i + 5] = offset + 0;

			offset += 4;
		}

		s_Storage->MeshVA = Zero::VertexArray::Create();
		
		s_Storage->MeshVB.reset(Zero::VertexBuffer::Create(s_Storage->MaxVertices * sizeof(MeshVertex)));
		s_Storage->MeshVB->SetLayout(quadLayout);

		s_Storage->MeshVA->AddVertexBuffer(s_Storage->MeshVB);

		s_Storage->MeshIB.reset(Zero::IndexBuffer::Create(s_Storage->MeshIndices, s_Storage->MaxIndices));
		s_Storage->MeshVA->SetIndexBuffer(s_Storage->MeshIB);
		

		for (int i = 0; i < s_Storage->MaxTextureSlots; i++)
		{
			s_Storage->Samplers[i] = i;
		}

		s_Storage->TexturedQuadShader = Shader::Create("src/shaders/textured_mesh.glsl");

		Zero::FramebufferSpecification framebufferSpec;

		framebufferSpec.Width = Zero::Application::GetInstance().GetWindow()->GetWidth() * 2.0f / 3.0f - 40.0f;
		framebufferSpec.Height = Zero::Application::GetInstance().GetWindow()->GetHeight() - 40.0f;
		framebufferSpec.ColorAttachment = 0;

		s_Storage->Framebuffer = Zero::Framebuffer::Create(framebufferSpec);

	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Storage->TexturedQuadShader->Bind();
		s_Storage->TexturedQuadShader->UploadData("u_TransformationMatrix",glm::mat4(1.0f));
		s_Storage->TexturedQuadShader->UploadData("u_ViewProjection", camera.GetViewProjectionMatrix());

		
		s_Storage->TexturedQuadShader->UploadData("u_TexUnits",s_Storage->Samplers.size(), s_Storage->Samplers.data());
		s_Storage->Framebuffer->Bind();
	}

	void Renderer2D::UpdateFramebuffer()
	{
		s_Storage->Framebuffer->Invalidate();
	}

	Ref<Framebuffer>& Renderer2D::GetFramebuffer()
	{
		return s_Storage->Framebuffer;
	}


	void Renderer2D::EndScene()
	{
		s_Storage->MeshVA->Bind();
		s_Storage->MeshVB->Bind();

		for (uint32_t i = 0; i < s_Storage->MaxTextureSlots; i++)
		{
			if (s_Storage->Textures[i] != nullptr)
			{
				//std::string textureInfo = "Binding texture " + std::to_string(i);
				//ZERO_CORE_INFO(textureInfo);
				s_Storage->Textures[i]->Bind();
			}
		}
		uint32_t size = (uint32_t)s_Storage->MeshVerticesPtr - (uint32_t)s_Storage->MeshVerticesBase;
		//std::string verticesCountString = "Total vertices :" + std::to_string(size);
		//ZERO_CORE_INFO(verticesCountString);
		s_Storage->MeshVB->SetData(s_Storage->MeshVerticesBase, size);
		
		Flush();
	}

	void Renderer2D::Flush()
	{
		
		RenderCommand::DrawIndexed(s_Storage->MeshVA,s_Storage->MeshIndicesCount);
		s_Storage->Framebuffer->Unbind();
	}

	void Renderer2D::Shutdown()
	{
		delete s_Storage;
	}

	void Renderer2D::AddQuadToBuffer(Quad* mesh,Ref<Texture2D> texture = nullptr)
	{
		auto vertices = mesh->GetVertices();
		for (int i = 0; i < vertices.size(); i++)
		{
			s_Storage->MeshVerticesPtr->Position = vertices[i].Position;
			s_Storage->MeshVerticesPtr->Color = vertices[i].Color;
			s_Storage->MeshVerticesPtr->Uv = vertices[i].Uv;
			s_Storage->MeshVerticesPtr->TexIndex = vertices[i].TexIndex;
			s_Storage->MeshVerticesPtr++;
		}

		s_Storage->MeshIndicesCount += 6;

		for (int i = 0; i < s_Storage->MaxTextureSlots; i++)
		{
			if (texture->GetTextureSlot() == i)
			{
				ZERO_CORE_INFO("Applied texture to texture array");
				s_Storage->Textures[i] = texture;
				break;
			}
		}
	}
	void Renderer2D::ClearBuffer()
	{
		s_Storage->MeshVerticesPtr = s_Storage->MeshVerticesBase;
		s_Storage->MeshIndicesCount = 0;
	}
}

