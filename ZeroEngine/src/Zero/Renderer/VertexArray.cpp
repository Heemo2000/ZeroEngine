#include "zeropch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
namespace Zero
{
	Zero::Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RenderAPI::API::None:
				ZERO_CORE_ASSERT(false, "No Renderer API Selected!!");
				return nullptr;

			case RenderAPI::API::OpenGL:
				return std::make_shared<OpenGLVertexArray>();
		}

		ZERO_CORE_ASSERT(false, "Unknown Renderer API!!");
		return nullptr;
	}
}