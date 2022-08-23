#pragma once
#include <glad/glad.h>
#include "Zero/Renderer/RenderAPI.h"


namespace Zero
{
	class OpenGLRenderAPI : public RenderAPI
	{
	public:
		virtual void SetClearColor(glm::vec4& color) override;
		virtual void Clear() override;
		virtual void DrawIndexed(Ref<VertexArray>& vertexArray) override;
	};
}
