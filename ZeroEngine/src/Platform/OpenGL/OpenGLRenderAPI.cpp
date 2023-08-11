#include "zeropch.h"
#include "OpenGLRenderAPI.h"

#include <glad/glad.h>
namespace Zero
{
	void OpenGLRenderAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
	}
	void OpenGLRenderAPI::SetClearColor(glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}
	void OpenGLRenderAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}
	void OpenGLRenderAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void OpenGLRenderAPI::DrawIndexed(Ref<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, (void*)0);
	}

	void OpenGLRenderAPI::DrawIndexed(Ref<VertexArray>& vertexArray, uint32_t count)
	{
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, (void*)0);
	}

	void OpenGLRenderAPI::DrawInstanced(Ref<VertexArray>& vertexArray,uint32_t instanceCount)
	{
		vertexArray->Bind();
		glDrawElementsInstanced(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, (void*)0, instanceCount);
	}
}