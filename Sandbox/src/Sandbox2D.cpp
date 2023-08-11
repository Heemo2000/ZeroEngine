#include "Sandbox2D.h"
#include "backends/imgui_impl_opengl3.h"

Sandbox2D::Sandbox2D() : m_CameraController(Zero::OrthographicCameraController(16.0f/9.0f,false,-1000.0f,1000.0f))
{
	Zero::Renderer::Init();
	Zero::Renderer2D::Init();

	//m_CameraController = Zero::OrthographicCameraController(16.0f / 9.0f, false);

	m_ClearColor.r = 0.0f;
	m_ClearColor.g = 0.0f;
	m_ClearColor.b = 0.0f;
	m_ClearColor.a = 1.0f;

	Zero::Ref<BrushData> whiteBrushData;
	whiteBrushData.reset(new BrushData(
							"White Brush",
							"F://Projects_and_program_files/ZeroEngine/Sandbox/textures/white_texture.png",
							0.0f,
							new float[4] {1.0f, 1.0f, 1.0f, 1.0f},
							0.5f)
						);

	m_Brushes.push_back(whiteBrushData);


	Zero::Ref<BrushData> smileyBrushData;
	
	smileyBrushData.reset(new BrushData("smiley brush",
						 "F://Projects_and_program_files/ZeroEngine/Sandbox/textures/smily.png",
						  1.0f,
						  new float[4]{1.0f, 1.0f, 1.0f, 1.0f},
						  0.5f)
						  );


	m_Brushes.push_back(smileyBrushData);

	Zero::Ref<BrushData> sandwichBrushData;

	sandwichBrushData.reset(new BrushData("sandwich brush",
								   "F://Projects_and_program_files/ZeroEngine/Sandbox/textures/sandwich.png",
								   2.0f,
								   new float[4] { 1.0f, 1.0f, 1.0f, 1.0f },
							       0.5f)
								   );

	m_Brushes.push_back(sandwichBrushData);
	m_CurrentBrush = m_Brushes[0];

}


glm::vec3 Sandbox2D::ScreenToWorldPoint(glm::vec3 position)
{
	glm::mat4 viewProjectionMatrix = m_CameraController.GetCamera().GetProjectionMatrix();
	glm::mat4 invertedMatrix = glm::inverse(viewProjectionMatrix);

	float w = 1.0f;
	glm::vec4 temp;
	temp.x = position.x;
	temp.y = position.y;
	temp.z = position.z;
	temp.w = w;

	glm::vec4 result = invertedMatrix * temp;
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return glm::vec3(result.x, result.y, result.z);

}

void Sandbox2D::CreateQuad(glm::vec3 position)
{
	//Calculate points in clockwise order.


	glm::vec3 point1 = position + glm::vec3(-1.0f, -1.0f, 0.0f) * m_CurrentBrush->BrushThickness;
	glm::vec3 point2 = position + glm::vec3(-1.0f, 1.0f, 0.0f) * m_CurrentBrush->BrushThickness;
	glm::vec3 point3 = position + glm::vec3(1.0f, 1.0f, 0.0f) * m_CurrentBrush->BrushThickness;
	glm::vec3 point4 = position + glm::vec3(1.0f, -1.0f, 0.0f) * m_CurrentBrush->BrushThickness;

	glm::vec4 vertexColor = glm::vec4(m_CurrentBrush->BrushColor[0], 
									  m_CurrentBrush->BrushColor[1], 
									  m_CurrentBrush->BrushColor[2], 
									  m_CurrentBrush->BrushColor[3]);
	Zero::MeshVertex v1;
	v1.Position = point1;
	v1.Color = vertexColor;
	v1.Uv = glm::vec2(0.0f, 0.0f);
	v1.TexIndex = m_CurrentBrush->BrushTexSlot;

	Zero::MeshVertex v2;
	v2.Position = point2;
	v2.Color = vertexColor;
	v2.Uv = glm::vec2(0.0f, 1.0f);
	v2.TexIndex = m_CurrentBrush->BrushTexSlot;

	Zero::MeshVertex v3;
	v3.Position = point3;
	v3.Color = vertexColor;
	v3.Uv = glm::vec2(1.0f, 1.0f);
	v3.TexIndex = m_CurrentBrush->BrushTexSlot;

	Zero::MeshVertex v4;
	v4.Position = point4;
	v4.Color = vertexColor;
	v4.Uv = glm::vec2(1.0f, 0.0f);
	v4.TexIndex = m_CurrentBrush->BrushTexSlot;

	Zero::Ref<Zero::Quad> quad;
	quad.reset(new Zero::Quad({ v1,v2,v3,v4 }));

	Zero::Renderer2D::AddQuadToBuffer(quad.get(),m_CurrentBrush->BrushTex);
}

void Sandbox2D::OnAttach()
{
}

void Sandbox2D::OnDetach()
{
	Zero::Renderer2D::ClearBuffer();
}

void Sandbox2D::OnUpdate(Zero::Timestep timestep)
{
	Zero::RenderCommand::SetClearColor(m_ClearColor);
	Zero::RenderCommand::Clear();

	Zero::Renderer::BeginScene(m_CameraController.GetCamera());
	Zero::Renderer2D::BeginScene(m_CameraController.GetCamera());

	m_CameraController.OnUpdate(timestep);
	
	if (Zero::Input::IsMouseButtonPressed(ZERO_MOUSE_BUTTON_LEFT))
	{
		m_MouseHold = true;
	}
	else if(Zero::Input::IsMouseButtonReleased(ZERO_MOUSE_BUTTON_LEFT))
	{
		m_MouseHold = false;
	}
	
	if (m_MouseHold)
	{
		
		auto mousePosPair = Zero::Input::GetMousePosNormalized();
		glm::vec3 mousePos;
		
		mousePos = glm::vec3(mousePosPair.first, mousePosPair.second, 0);

		glm::vec3 worldPos = ScreenToWorldPoint(mousePos);
		worldPos.z = m_ZIndex;
		float distance = glm::distance(m_PreviousPoint, worldPos);
		float clearQuadVecDistance = 2 * m_QuadDrawMinDistance;
		
		if (distance >= m_QuadDrawMinDistance)
		{
			glm::vec3 direction = glm::normalize(worldPos - m_PreviousPoint);
			m_PreviousPoint = worldPos;
			CreateQuad(worldPos);
		}
	}
	
	
	Zero::Renderer2D::EndScene();
	Zero::Renderer::EndScene();
}

void Sandbox2D::OnEvent(Zero::Event& event)
{
	Zero::EventDispatcher eventDispatcher(event);
	eventDispatcher.Dispatch<Zero::WindowResizedEvent>(ZERO_BIND_EVENT_FN(Sandbox2D::OnWindowResized));
	eventDispatcher.Dispatch<Zero::KeyPressedEvent>(ZERO_BIND_EVENT_FN(Sandbox2D::OnKeyPressed));
	eventDispatcher.Dispatch<Zero::KeyTypedEvent>(ZERO_BIND_EVENT_FN(Sandbox2D::OnKeyTyped));
	eventDispatcher.Dispatch<Zero::MouseScrolledEvent>(ZERO_BIND_EVENT_FN(Sandbox2D::OnMouseScrolled));
	eventDispatcher.Dispatch<Zero::MouseButtonClickedEvent>(ZERO_BIND_EVENT_FN(Sandbox2D::OnMouseClicked));

	m_CameraController.OnEvent(event);
}

void Sandbox2D::OnImGuiRender()
{
	ImGuiWindowFlags windowFlags = 0;
	windowFlags |= ImGuiWindowFlags_NoResize;
	ImGui::Begin("Settings",&m_Open, windowFlags);
	ImGui::ColorPicker4("Brush Color :", m_CurrentBrush->BrushColor);
	ImGui::Text("Clear the shapes:");
	if (ImGui::Button("Clear"))
	{
		Zero::Renderer2D::ClearBuffer();
		m_ZIndex = -990.0f;
	}
	ImGui::SliderFloat("Brush Width", &m_CurrentBrush->BrushThickness, 0.2f, 1.0f,"%.3f", ImGuiSliderFlags_AlwaysClamp);
	
	uint32_t brushesInRow = 0;
	ImGui::Text("Textured buttons");
	for (int i = 0; i < m_Brushes.size(); i++)
	{
		if (brushesInRow == BrushesPerLine)
		{
			ImGui::NewLine();
			brushesInRow = 0;
		}
		Zero::Ref<BrushData> brushData = m_Brushes[i];
		float my_tex_w = (float)brushData->BrushTex->GetWidth();
		float my_tex_h = (float)brushData->BrushTex->GetHeight();

		ImGui::PushID(i);
		int frame_padding = -1 + i;
		ImVec2 size = ImVec2(32.0f, 32.0f);
		ImVec2 uv0 = ImVec2(-1.0f, 1.0f); //Bottom-Left
		ImVec2 uv1 = ImVec2(0.0f, 0.0f);

		ImVec4 bg_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
		ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
		if (ImGui::ImageButton((void*)(intptr_t)(brushData->BrushTex->GetTextureID()), size, uv0, uv1, frame_padding, bg_col, tint_col))
		{
			m_CurrentBrush = brushData;
			m_ZIndex++;
		}
		ImGui::SameLine();
		ImGui::PopID();
		brushesInRow++;
	}
	
	ImGui::End();
	
	
}

bool Sandbox2D::OnWindowResized(Zero::WindowResizedEvent& event)
{
	return true;
}

bool Sandbox2D::OnKeyPressed(Zero::KeyPressedEvent& event)
{
	return true;
}

bool Sandbox2D::OnKeyTyped(Zero::KeyTypedEvent& event)
{
	return true;
}

bool Sandbox2D::OnMouseScrolled(Zero::MouseScrolledEvent& event)
{
	return true;
}

bool Sandbox2D::OnMouseClicked(Zero::MouseButtonClickedEvent& event)
{
	return true;
}
