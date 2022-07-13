#pragma once
#include "RenderAPI.h"


namespace Zero
{
	class ZERO_API RenderCommand
	{
	public:
		inline static void SetClearColor(glm::vec4& color) { s_RenderAPI->SetClearColor(color); }
		inline static void Clear() { s_RenderAPI->Clear(); };
		inline static void DrawIndexed(std::shared_ptr<VertexArray>& vertexArray) { s_RenderAPI->DrawIndexed(vertexArray); }
	private:
		static RenderAPI* s_RenderAPI;
	};
}