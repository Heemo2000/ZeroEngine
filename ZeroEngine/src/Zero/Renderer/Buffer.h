#pragma once


namespace Zero
{
	class VertexBuffer
	{
	public:
		static VertexBuffer* Create(float* vertices, uint32_t size);
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual ~VertexBuffer() {};
	};


	class IndexBuffer
	{
	public:
		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
		virtual uint32_t GetCount() = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual ~IndexBuffer() {};
	};
}

