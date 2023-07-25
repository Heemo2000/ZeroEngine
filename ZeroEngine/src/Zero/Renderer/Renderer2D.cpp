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
		const uint32_t MaxMeshes = 1000;
		const uint32_t MaxVertices = MaxMeshes * 4;
		const uint32_t MaxIndices = MaxMeshes * 6;
		
		Ref<VertexArray> MeshVA;
		Ref<VertexBuffer> MeshVB;
		Ref<IndexBuffer> MeshIB;
		Ref<Shader> FlatColorShader;
		
		MeshVertex* MeshVerticesBase;
		MeshVertex* MeshVerticesPtr;
		
		std::unordered_map<Quad*, MeshVertex*> QuadsMap;
		uint32_t MeshIndicesCount = 0;
		uint32_t* MeshIndices;

	};

	static Renderer2DStorage* s_Storage;

	void Renderer2D::Init()
	{
		s_Storage = new Renderer2DStorage();

		BufferLayout quadLayout =
		{
			{"a_Position",ShaderDataType::Float3},
			{"a_Color",ShaderDataType::Float4}
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
		
		s_Storage->FlatColorShader = Shader::Create("src/shaders/mesh.glsl");
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Storage->FlatColorShader->Bind();
		s_Storage->FlatColorShader->UploadData("u_TransformationMatrix",glm::mat4(1.0f));
		s_Storage->FlatColorShader->UploadData("u_ViewProjection", camera.GetViewProjectionMatrix());
		
	}

	void Renderer2D::EndScene()
	{
		s_Storage->MeshVA->Bind();
		s_Storage->MeshVB->Bind();
		uint32_t size = (uint32_t)s_Storage->MeshVerticesPtr - (uint32_t)s_Storage->MeshVerticesBase;
		//std::string verticesCountString = "Total vertices :" + std::to_string(size);
		//ZERO_CORE_INFO(verticesCountString);
		s_Storage->MeshVB->SetData(s_Storage->MeshVerticesBase, size);
		Flush();
	}

	void Renderer2D::Flush()
	{
		
		RenderCommand::DrawIndexed(s_Storage->MeshVA,s_Storage->MeshIndicesCount);
	}

	void Renderer2D::Shutdown()
	{
		delete s_Storage;
	}

	void Renderer2D::AddQuadToBuffer(Quad* mesh)
	{
		auto vertices = mesh->GetVertices();

		s_Storage->QuadsMap[mesh] = s_Storage->MeshVerticesPtr;
		for (int i = 0; i < vertices.size(); i++)
		{
			s_Storage->MeshVerticesPtr->Position = vertices[i].Position;
			s_Storage->MeshVerticesPtr->Color = vertices[i].Color;
			s_Storage->MeshVerticesPtr++;
		}

		s_Storage->MeshIndicesCount += 6;

		ZERO_CORE_INFO("Meshes Count after adding mesh: " + std::to_string(s_Storage->QuadsMap.size()));
	}
	void Renderer2D::UpdateQuad(Quad* quad, std::vector<MeshVertex> vertices)
	{
		auto location = s_Storage->QuadsMap.find(quad);
		if (location != s_Storage->QuadsMap.end())
		{
			ZERO_CORE_INFO("Updating quad vertices");
			for (int i = 0; i < 4; i++)
			{
				uint32_t verticesStartIndex = (uint32_t)location->second - (uint32_t)s_Storage->MeshVerticesBase;
				//std::string message = "vertices start index : " + std::to_string(verticesStartIndex);
				//ZERO_CORE_INFO(message);
				(s_Storage->MeshVerticesBase + verticesStartIndex + i)->Position = vertices[i].Position;
			}
		}
	}
	void Renderer2D::ClearBuffer()
	{
		s_Storage->MeshVerticesPtr = s_Storage->MeshVerticesBase;
		s_Storage->MeshIndicesCount = 0;
		s_Storage->QuadsMap.clear();
	}
}

