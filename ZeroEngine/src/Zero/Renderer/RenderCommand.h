#pragma once
#include "RenderAPI.h"


namespace Zero
{
	class ZERO_API RenderCommand
	{
	public:
		static void Init();
		inline static void SetClearColor(glm::vec4& color) { s_RenderAPI->SetClearColor(color); }
		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { s_RenderAPI->SetViewport(x, y, width, height); };
		inline static void Clear() { s_RenderAPI->Clear(); };
		inline static void DrawIndexed(Ref<VertexArray>& vertexArray) { s_RenderAPI->DrawIndexed(vertexArray); }
		inline static void DrawIndexed(Ref<VertexArray>& vertexArray,uint32_t count) { s_RenderAPI->DrawIndexed(vertexArray,count); }
		inline static void DrawInstanced(Ref<VertexArray>& vertexArray,uint32_t instanceCount) { s_RenderAPI->DrawInstanced(vertexArray,instanceCount); }
	
	private:
		static RenderAPI* s_RenderAPI;
	};
}