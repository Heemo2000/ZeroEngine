#include "zeropch.h"
#include "Zero/Renderer/Renderer.h"
#include "Framebuffer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Zero
{
	Ref<Framebuffer> Zero::Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:
			ZERO_CORE_ASSERT(false, "No Renderer API Selected!!");
			return nullptr;

		case RenderAPI::API::OpenGL:
			return std::make_shared<OpenGLFramebuffer>(spec);
		}

		ZERO_CORE_ASSERT(false, "Unknown Renderer API!!");
		return nullptr;
	}
	std::string Framebuffer::GetFramebufferDetails()
	{
		std::string result = "";
		result += "Framebuffer Details::\n";
		result += "Width: " + std::to_string(m_Spec.Width) + "\n";
		result += "Height: " + std::to_string(m_Spec.Height) + "\n";
		result += "Color Attachment: " + std::to_string(m_Spec.ColorAttachment);

		return result;
	}
}

