#pragma once
#include <vector>
#include "Zero/Renderer/Buffer.h"
#include "Zero/Renderer/VertexArray.h"


namespace Zero
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual void Bind() override;
		virtual void Unbind() override;
		virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer) override;
		virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer) override;
		virtual std::shared_ptr<IndexBuffer> GetIndexBuffer() const override;
		virtual ~OpenGLVertexArray() override;

	private:
		std::vector <std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		uint32_t m_RendererID;
	};
}
