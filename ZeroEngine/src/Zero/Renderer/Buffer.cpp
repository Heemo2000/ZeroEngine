#include "zeropch.h"
#include "Buffer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Renderer.h"



namespace Zero
{
	template<typename T>
	VertexBuffer* VertexBuffer::Create(T* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RenderAPI::API::None:
						ZERO_CORE_ASSERT(false, "No Renderer API Selected!!");
						return nullptr;
			
			case RenderAPI::API::OpenGL:
						return new OpenGLVertexBuffer(vertices, size);
		}

		ZERO_CORE_ASSERT(false, "Unknown Renderer API!!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RenderAPI::API::None:
						ZERO_CORE_ASSERT(false, "No Renderer API Selected!!");
						return nullptr;
			
			case RenderAPI::API::OpenGL:
						return new OpenGLIndexBuffer(indices, count);
		}

		ZERO_CORE_ASSERT(false, "Unknown Renderer API!!");
		return nullptr;
	}
}



