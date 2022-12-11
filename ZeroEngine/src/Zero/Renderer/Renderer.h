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
		static void Init();
		static void OnWindowResize(uint32_t width, uint32_t height);
		static void BeginScene();
		static void BeginScene(OrthographicCamera camera);
		static void Submit(Ref<Shader>& shader,Ref<VertexArray>& vertexArray, const glm::mat4& transformMatrix);
		static void Submit(Ref<Shader>& shader, Ref<VertexArray>& vertexArray, const glm::mat4& transformMatrix, uint32_t instanceCount);
		static void EndScene();
		static inline RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }
	

	private:
		static SceneData* m_SceneData;
	};
}



