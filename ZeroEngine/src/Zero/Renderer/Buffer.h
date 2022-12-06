#pragma once
#include <string>
#include <vector>

enum class ShaderDataType
{
	None = 0,
	Int,
	Int2,
	Int3,
	Int4,
	Float,
	Float2,
	Float3,
	Float4,
	Mat3,
	Mat4,
	Bool
};

static uint32_t GetShaderDataTypeSize(ShaderDataType type)
{
	switch (type)
	{
		case ShaderDataType::Int:       return 4;
		case ShaderDataType::Int2:      return 4 * 2;
		case ShaderDataType::Int3:      return 4 * 3;
		case ShaderDataType::Int4:      return 4 * 4;
		case ShaderDataType::Float:     return 4;
		case ShaderDataType::Float2:    return 4 * 2;
		case ShaderDataType::Float3:    return 4 * 3;
		case ShaderDataType::Float4:    return 4 * 4;
		case ShaderDataType::Mat3:      return 4 * 3 * 3;
		case ShaderDataType::Mat4:      return 4 * 4 * 4;
		case ShaderDataType::Bool:      return 1;
	}

	ZERO_CORE_ASSERT(false, "Unknown shader data type!!");
	return 0;
}

struct BufferElement
{
	std::string Name;
	ShaderDataType Type;
	uint32_t Size;
	uint32_t OffSet;
	bool Normalized;

	BufferElement(std::string name,ShaderDataType type,bool normalized = false) : Name(name),Type(type),
																				  Size(GetShaderDataTypeSize(type)),
																				  OffSet(0), Normalized(normalized)
																				  {}
	
	uint32_t GetComponentCount()
	{
		switch (Type)
		{
		     case ShaderDataType::Int:      return 1;
		     case ShaderDataType::Int2:     return 2;
		     case ShaderDataType::Int3:     return 3;
			 case ShaderDataType::Int4:     return 4;
		     case ShaderDataType::Float:    return 1;
		     case ShaderDataType::Float2:   return 2;
		     case ShaderDataType::Float3:   return 3;
			 case ShaderDataType::Float4:   return 4;
		     case ShaderDataType::Mat3:     return 3 * 3;
		     case ShaderDataType::Mat4:     return 4 * 4;
		     case ShaderDataType::Bool:     return 1;
		}

		ZERO_CORE_ASSERT(false, "Unknown component count!!");
		return 0;
	}
};

class ZERO_API BufferLayout
{
public:
	BufferLayout() {};
	BufferLayout(std::initializer_list<BufferElement> elements) : m_Elements(elements),m_Stride(0)
	{
		CalculateStrideAndOffSet();
	}
	inline const uint32_t GetStride() const { return m_Stride; }

	std::vector<BufferElement> GetElements() const { return m_Elements; }
	std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
	std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
private:
	void CalculateStrideAndOffSet()
	{
		m_Stride = 0;
		uint32_t offSet = 0;
		for (BufferElement& element : m_Elements)
		{
			element.OffSet = offSet;
			offSet += element.Size;
			m_Stride += element.Size;
		}
	}
private:
	std::vector<BufferElement> m_Elements;
	uint32_t m_Stride = 0;
};
namespace Zero
{
	class ZERO_API VertexBuffer
	{
	public:
		
		static VertexBuffer* Create(float* vertices, uint32_t size);
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual ~VertexBuffer() {};
	};


	class ZERO_API IndexBuffer
	{
	public:
		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
		virtual uint32_t GetCount() = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual ~IndexBuffer() {};
	};
}

