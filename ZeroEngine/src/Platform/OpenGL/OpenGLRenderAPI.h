#pragma once
#include "Zero/Renderer/RenderAPI.h"


namespace Zero
{
	class OpenGLRenderAPI : public RenderAPI
	{
	public:
		virtual void Init() override;
		virtual void SetClearColor(glm::vec4& color) override;
		virtual void Clear() override;
		virtual void DrawIndexed(Ref<VertexArray>& vertexArray) override;
	};
}
