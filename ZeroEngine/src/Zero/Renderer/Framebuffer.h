#pragma once
#include<string>

namespace Zero
{
	struct FramebufferSpecification
	{
		uint32_t Width;
		uint32_t Height;
		uint32_t ColorAttachment;
	};
	class Framebuffer
	{
	public:
		static Ref<Framebuffer> Create(const FramebufferSpecification& spec);
		void virtual Invalidate() = 0;
		void virtual Bind() = 0;
		void virtual Unbind() = 0;
		uint32_t virtual GetFramebufferTexID() const = 0;
		~Framebuffer() {}

	public:
		inline FramebufferSpecification GetFramebufferSpecification() { return m_Spec; }
		inline void SetFramebufferSpecification(FramebufferSpecification spec) { m_Spec = spec; }
		std::string GetFramebufferDetails();
	protected:
		FramebufferSpecification m_Spec;
	};
}


