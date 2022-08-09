#include "zeropch.h"
#include "Renderer.h"
#include "Zero/Core/Transform.h"
namespace Zero
{
	SceneData* Renderer::m_SceneData = new SceneData();
	void Renderer::BeginScene()
	{

	}

	void Renderer::BeginScene(std::shared_ptr<OrthographicCamera>& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera->GetViewProjectionMatrix();
	}

	void Renderer::Submit(std::shared_ptr<Shader>& shader,std::shared_ptr<VertexArray>& vertexArray,const glm::mat4& transformMatrix)
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
