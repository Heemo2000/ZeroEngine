#pragma once
#include "RenderCommand.h"

namespace Zero
{
	class ZERO_API Renderer
	{
	public:
		static void BeginScene();
		static void Submit(std::shared_ptr<VertexArray>& vertexArray);
		static void EndScene();
		static inline RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }
	};
}



