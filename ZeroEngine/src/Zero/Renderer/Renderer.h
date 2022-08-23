#pragma once
#include <memory>
#include "RenderCommand.h"
#include "Zero/Renderer/OrthographicCamera.h"
#include "Zero/Renderer/Shader.h"
namespace Zero
{
	struct SceneData
	{
		glm::mat4 ViewProjectionMatrix = glm::mat4(1.0f);
	};
	class ZERO_API Renderer
	{
	public:
		static void BeginScene();
		static void BeginScene(Ref<OrthographicCamera>& camera);
		static void Submit(Ref<Shader>& shader,Ref<VertexArray>& vertexArray, const glm::mat4& transformMatrix);
		static void EndScene();
		static inline RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }
	

	private:
		static SceneData* m_SceneData;
	};
}



