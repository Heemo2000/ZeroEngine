#include "zeropch.h"
#include "Buffer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Renderer.h"



namespace Zero
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:
						ZERO_CORE_ASSERT(false, "No Renderer API Selected!!");
						return nullptr;
			
			case RendererAPI::OpenGL:
						return new OpenGLVertexBuffer(vertices, size);
		}

		ZERO_CORE_ASSERT(false, "Unknown Renderer API!!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:
						ZERO_CORE_ASSERT(false, "No Renderer API Selected!!");
						return nullptr;
			
			case RendererAPI::OpenGL:
						return new OpenGLIndexBuffer(indices, count);
		}

		ZERO_CORE_ASSERT(false, "Unknown Renderer API!!");
		return nullptr;
	}
}



