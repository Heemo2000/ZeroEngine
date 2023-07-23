#pragma once
#include <glm/glm.hpp>
#include "OrthographicCamera.h"
#include "Mesh.h"
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
		static void AddMeshToBuffer(Mesh mesh);
	};
}