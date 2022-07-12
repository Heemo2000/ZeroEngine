#pragma once

#include <vector>
#include <memory>
#include "Buffer.h"

namespace Zero
{

	class ZERO_API VertexArray
	{
	public:
		static VertexArray* Create();
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer) = 0;
		virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer) = 0;
		virtual std::shared_ptr<IndexBuffer> GetIndexBuffer() const = 0;
		virtual ~VertexArray() {}
	};
}
