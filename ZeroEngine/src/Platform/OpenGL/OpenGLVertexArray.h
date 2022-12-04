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
		virtual void AddVertexBuffer(Ref<VertexBuffer> vertexBuffer) override;
		virtual void SetIndexBuffer(Ref<IndexBuffer> indexBuffer) override;
		virtual Ref<IndexBuffer> GetIndexBuffer() const override;
		virtual ~OpenGLVertexArray() override;

	private:
		std::vector <Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_QuadIB;
		uint32_t m_RendererID;
	};
}
