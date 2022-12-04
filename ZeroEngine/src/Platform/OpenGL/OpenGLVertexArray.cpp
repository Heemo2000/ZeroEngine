#include "zeropch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Zero
{
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_RendererID);
	}
	void OpenGLVertexArray::Bind()
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(Ref<VertexBuffer> vertexBuffer)
	{
		ZERO_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!!");

		glBindVertexArray(m_RendererID);
		m_VertexBuffers.push_back(vertexBuffer);
		vertexBuffer->Bind();

		BufferLayout layout = vertexBuffer->GetLayout();
		uint32_t i = 0;
		for (BufferElement& element : layout)
		{

			glVertexAttribPointer(i, element.GetComponentCount(), GL_FLOAT, element.Normalized ? GL_TRUE : GL_FALSE,
								  layout.GetStride(), (void*)element.OffSet);
			glEnableVertexAttribArray(i);
			i++;
		}
	}

	void OpenGLVertexArray::SetIndexBuffer(Ref<IndexBuffer> indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		m_QuadIB = indexBuffer;
		m_QuadIB->Bind();
	}

	Ref<IndexBuffer> OpenGLVertexArray::GetIndexBuffer() const
	{
		return m_QuadIB;
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}
}