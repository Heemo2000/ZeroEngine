#include "zeropch.h"
#include "OpenGLRenderAPI.h"

#include <glad/glad.h>
namespace Zero
{
	void OpenGLRenderAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		//glEnable(GL_DEPTH_TEST);
	}
	void OpenGLRenderAPI::SetClearColor(glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}
	void OpenGLRenderAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	std::string OpenGLRenderAPI::ReadPixel(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		std::string pixelInfo;
		if (x <= width && y <= height)
		{
			unsigned char temp[4];

			glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, temp);

			pixelInfo.append("R: ");
			pixelInfo.append("" + std::to_string(temp[0]));


			pixelInfo.append(",G: ");
			pixelInfo.append("" + std::to_string(temp[1]));

			pixelInfo.append(",B: ");
			pixelInfo.append("" + std::to_string(temp[2]));

			pixelInfo.append(",A: ");
			pixelInfo.append("" + std::to_string(temp[3]));
		}
		else
		{
			pixelInfo = "Invalid position for reading a pixel";
		}

		return pixelInfo;
	}
	void OpenGLRenderAPI::Clear()
	{
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT);
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