#pragma once
#include <Zero.h>
#include <glm/glm.hpp>
#include "backends/imgui_impl_opengl3.h"


struct BrushData
{
	std::string BrushName;
	std::string BrushTexFilePath;
	Zero::Ref<Zero::Texture2D> BrushTex;
	float BrushTexSlot;
	float BrushColor[4];
	float BrushThickness = 0.5f;


	BrushData(std::string brushName, std::string brushTexFilePath,float textureSlot,
		float brushColor[4], float brushThickness)
	{
		BrushName = brushName;
		BrushTexFilePath = brushTexFilePath;
		BrushTex.reset(Zero::Texture2D::Create(brushTexFilePath, (int)textureSlot));
		BrushTexSlot = textureSlot;
		for (int i = 0; i < 4; i++)
		{
			BrushColor[i] = brushColor[i];
		}

		BrushThickness = brushThickness;
	}

	BrushData(std::string brushName, uint32_t eachPixelData, float textureSlot, float brushColor[4], float brushThickness)
	{
		BrushName = brushName;
		BrushTexFilePath = "";
		BrushTex.reset(Zero::Texture2D::Create(eachPixelData, (int)textureSlot));
		BrushTexSlot = textureSlot;
		for (int i = 0; i < 4; i++)
		{
			BrushColor[i] = brushColor[i];
		}

		BrushThickness = brushThickness;
	}
};


class Sandbox2D : public Zero::Layer
{
public:
	Sandbox2D();
	void OnDetach() override;
	void OnAttach() override;
	void OnUpdate(Zero::Timestep timestep) override;
	void OnEvent(Zero::Event& event) override;
	void OnImGuiRender() override;

private:
	glm::vec3 ScreenToWorldPoint(glm::vec3 position);
	void CreateQuad(glm::vec3 position);

	void SceneSection(bool* show);
	void OptionsSection(bool* show);

private:
	bool OnWindowResized(Zero::WindowResizedEvent& event);
	bool OnKeyPressed(Zero::KeyPressedEvent& event);
	bool OnKeyTyped(Zero::KeyTypedEvent& event);
	bool OnMouseScrolled(Zero::MouseScrolledEvent& event);
	bool OnMouseClicked(Zero::MouseButtonClickedEvent& event);

private:
	Zero::OrthographicCameraController m_CameraController;
	glm::vec4 m_ClearColor;

	glm::vec3 m_CameraPosition = glm::vec3(0.0f, 0.0f, 1.0f);
	float m_CameraMoveSpeed = 1.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 20.0f;

	float m_ElapsedTime = 0.0f;

	
	bool m_MouseHold;
	glm::vec3 m_PreviousPoint = glm::vec3(0.0f,0.0f,0.0f);
	float m_QuadDrawMinDistance = 0.5f;

	std::vector<Zero::Ref<BrushData>> m_Brushes;
	Zero::Ref<BrushData> m_CurrentBrush;
	Zero::Ref<Zero::Framebuffer> m_Framebuffer;
	const uint32_t BrushesPerLine = 3;

};