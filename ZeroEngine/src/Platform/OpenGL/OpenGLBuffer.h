#pragma once
#include "Zero/Renderer/Buffer.h"

namespace Zero
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual void Bind() override;
		virtual void Unbind() override;
		virtual ~OpenGLVertexBuffer() override;
	private:
		uint32_t m_RendererID;
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
