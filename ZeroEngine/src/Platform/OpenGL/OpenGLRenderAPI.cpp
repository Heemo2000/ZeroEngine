#include "zeropch.h"
#include "OpenGLRenderAPI.h"

namespace Zero
{
	void OpenGLRenderAPI::SetClearColor(glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}
	void OpenGLRenderAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	}
	void OpenGLRenderAPI::DrawIndexed(Ref<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, (void*)0);
	}
}