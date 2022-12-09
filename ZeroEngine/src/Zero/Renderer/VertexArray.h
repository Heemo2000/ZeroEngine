#pragma once

#include <vector>
#include <memory>
#include "Buffer.h"

namespace Zero
{

	class ZERO_API VertexArray
	{
	public:
		static Zero::Ref<VertexArray> Create();
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void AddVertexBuffer(Ref<VertexBuffer> vertexBuffer) = 0;
		virtual void SetIndexBuffer(Ref<IndexBuffer> indexBuffer) = 0;
		virtual Ref<IndexBuffer> GetIndexBuffer() const = 0;
		virtual ~VertexArray() {}
	};
}
