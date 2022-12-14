#pragma once
#include <glm/glm.hpp>
#include "OrthographicCamera.h"
namespace Zero
{
	class Renderer2D
	{
	public:
		static void Init();
		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		static void Shutdown();
		static void DrawQuad(const glm::vec2& position,const glm::vec2& scale,const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec3& scale, const glm::vec4& color);
	};
}