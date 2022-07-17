#include "zeropch.h"
#include "Renderer.h"
#include "Zero/Application.h"

namespace Zero
{
	void Renderer::BeginScene()
	{

	}

	void Renderer::BeginScene(std::shared_ptr<OrthographicCamera>& camera)
	{
		Application& app = Application::GetInstance();
		camera->SetWidth(app.GetWindow()->GetWidth());
		camera->SetHeight(app.GetWindow()->GetHeight());
	}
	
	void Renderer::Submit(std::shared_ptr<OrthographicCamera>& camera, std::shared_ptr<Shader>& shader)
	{
		camera->CalculateViewProjectionMatrix();
		shader->Bind();
		shader->UploadData("viewProjection", camera->GetViewProjectionMatrix());
	}

	void Renderer::Submit(std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::EndScene()
	{

	}
}
