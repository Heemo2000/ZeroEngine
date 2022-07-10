#include "zeropch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
namespace Zero
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:
				ZERO_CORE_ASSERT(false, "No Renderer API Selected!!");
				return nullptr;

			case RendererAPI::OpenGL:
				return new OpenGLVertexArray();
		}

		ZERO_CORE_ASSERT(false, "Unknown Renderer API!!");
		return nullptr;
	}
}