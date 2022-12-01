#pragma once
#include "RenderAPI.h"


namespace Zero
{
	class ZERO_API RenderCommand
	{
	public:
		static void Init();
		inline static void SetClearColor(glm::vec4& color) { s_RenderAPI->SetClearColor(color); }
		inline static void Clear() { s_RenderAPI->Clear(); };
		inline static void DrawIndexed(Ref<VertexArray>& vertexArray) { s_RenderAPI->DrawIndexed(vertexArray); }
		inline static void DrawInstanced(Ref<VertexArray>& vertexArray,uint32_t instanceCount) { s_RenderAPI->DrawInstanced(vertexArray,instanceCount); }
	private:
		static RenderAPI* s_RenderAPI;
	};
}