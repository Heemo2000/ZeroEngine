#pragma once
#include <glm/glm.hpp>
#include <memory>
#include "VertexArray.h"

namespace Zero
{
	class RenderAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL = 1
		};

	public:
		virtual void Init() = 0;
		virtual void SetClearColor(glm::vec4& color) = 0;
		virtual void Clear() = 0;
		virtual void DrawIndexed(Ref<VertexArray>& vertexArray) = 0;
		static inline API GetAPI() { return s_RenderAPIType; }
	private:
		static API s_RenderAPIType;
	};
}
