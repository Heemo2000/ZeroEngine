#include "zeropch.h"
#include "Renderer.h"


namespace Zero
{
	void Renderer::BeginScene()
	{

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
