#include "zeropch.h"
#include "Renderer.h"
#include "Zero/Core/Transform.h"
namespace Zero
{
	SceneData* Renderer::m_SceneData = new SceneData();
	void Renderer::Init()
	{
		RenderCommand::Init();
	}
	void Renderer::BeginScene()
	{

	}

	void Renderer::BeginScene(Ref<OrthographicCamera>& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera->GetViewProjectionMatrix();
	}

	void Renderer::Submit(Ref<Shader>& shader,Ref<VertexArray>& vertexArray,const glm::mat4& transformMatrix)
	{
		shader->Bind();
		shader->UploadData("u_TransformationMatrix", transformMatrix);
		shader->UploadData("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::EndScene()
	{

	}
}
