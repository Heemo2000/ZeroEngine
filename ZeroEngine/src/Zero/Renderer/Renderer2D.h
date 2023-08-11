#pragma once
#include <glm/glm.hpp>
#include "OrthographicCamera.h"
#include "Quad.h"
#include "Zero/Renderer/Texture.h"
namespace Zero
{
	class Renderer2D
	{
	public:
		static void Init();
		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		static void Flush();
		static void Shutdown();
		static void AddQuadToBuffer(Quad* quad,Ref<Texture2D> texture);
		static void UpdateQuad(Quad* quad,std::vector<MeshVertex> vertices);
		static void ClearBuffer();
	};
}