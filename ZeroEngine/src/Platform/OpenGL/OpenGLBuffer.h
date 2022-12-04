#pragma once
#include "Zero/Renderer/Buffer.h"

namespace Zero
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(const void* vertices, uint32_t size);
		virtual void Bind() override;
		virtual void Unbind() override;
		inline virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		inline virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
		virtual ~OpenGLVertexBuffer() override;
	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};


	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual void Bind() override;
		virtual void Unbind() override;
		virtual uint32_t GetCount() override;
		virtual ~OpenGLIndexBuffer() override;
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
}
