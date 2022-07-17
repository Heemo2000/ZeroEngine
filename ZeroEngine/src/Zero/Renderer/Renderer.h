#pragma once
#include <memory>
#include "RenderCommand.h"
#include "Zero/Renderer/OrthographicCamera.h"
#include "Zero/Renderer/Shader.h"
namespace Zero
{
	class ZERO_API Renderer
	{
	public:
		static void BeginScene();
		static void BeginScene(std::shared_ptr<OrthographicCamera>& camera);
		static void Submit(std::shared_ptr<OrthographicCamera>& camera, std::shared_ptr<Shader>& shader);
		static void Submit(std::shared_ptr<VertexArray>& vertexArray);
		static void EndScene();
		static inline RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }
	};
}



