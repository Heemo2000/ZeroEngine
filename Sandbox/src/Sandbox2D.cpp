#include "Sandbox2D.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui_internal.h"

Sandbox2D::Sandbox2D() : m_CameraController(Zero::OrthographicCameraController(16.0f/9.0f,false,-1000.0f,1000.0f))
{
	Zero::Renderer::Init();
	Zero::Renderer2D::Init();

	m_MainWindowClearColor.r = 1.0f;
	m_MainWindowClearColor.g = 1.0f;
	m_MainWindowClearColor.b = 1.0f;
	m_MainWindowClearColor.a = 1.0f;

	m_FramebufferClearColor.r = 0.5f;
	m_FramebufferClearColor.g = 0.5f;
	m_FramebufferClearColor.b = 0.5f;
	m_FramebufferClearColor.a = 1.0f;


	Zero::Ref<BrushData> whiteBrushData;
	whiteBrushData.reset(new BrushData(
							"White Brush",
							"F://Projects_and_program_files/ZeroEngine/Sandbox/textures/white_texture.png",
							0.0f,
							new float[4] {0.0f, 0.0f, 0.0f, 1.0f},
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

	ImGuiIO& io = ImGui::GetIO();

	io.WantSaveIniSettings = true;
	io.LogFilename = "ImGui Log.log";
	io.IniFilename = "ImGui Config.ini";
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.WantCaptureMouse = true;

	//ZERO_CLIENT_INFO(Zero::Renderer2D::GetFramebuffer()->GetFramebufferDetails());
}


glm::vec3 Sandbox2D::ScreenToWorldPoint(glm::vec3 position)
{
	glm::mat4 viewProjectionMatrix = m_CameraController.GetCamera().GetProjectionMatrix();
	glm::mat4 invertedMatrix = glm::inverse(viewProjectionMatrix);

	//float w = 1.0f;
	glm::vec4 temp;
	temp.x = position.x;
	temp.y = position.y;
	temp.z = position.z;
	temp.w = 1.0f;

	glm::vec4 result = invertedMatrix * temp;
	result.x /= temp.w;
	result.y /= temp.w;
	result.z /= temp.w;

	return glm::vec3(result.x, result.y, result.z);

}

bool Sandbox2D::CreateQuad()
{
	if (m_Points.size() == 2)
	{
		//Calculate points in clockwise order.

		float height = m_CurrentBrush->BrushThickness;

		glm::vec3 direction1 = glm::normalize(m_Points[1] - m_Points[0]);
		glm::vec3 forward = glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3 crossVector1 = glm::cross(direction1, forward);

		glm::vec3 backward = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 crossVector2 = glm::cross(direction1, backward);

		glm::vec3 point1 = m_Points[0] + crossVector1 * height / 2.0f;
		glm::vec3 point2 = m_Points[0] + crossVector2 * height / 2.0f;

		glm::vec3 direction2 = glm::normalize(m_Points[0] - m_Points[1]);
		glm::vec3 crossVector3 = glm::cross(direction2, forward);

		glm::vec3 crossVector4 = glm::cross(direction2, backward);


		glm::vec3 point3 = m_Points[1] + crossVector3 * height / 2.0f;
		glm::vec3 point4 = m_Points[1] + crossVector4 * height / 2.0f;

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
		auto vertices = std::vector<Zero::MeshVertex>{ v1,v2,v3,v4 };
		quad.reset(new Zero::Quad(vertices));

		Zero::Renderer2D::AddQuadToBuffer(quad.get(), m_CurrentBrush->BrushTex);
		m_Points.clear();

		return true;
	}

	return false;
}

void Sandbox2D::SceneSection(bool* show)
{
	//int currentId = 0;

	//Scene Section window configuration.


	ImGuiWindowFlags sceneSectionWindowFlags = 0;
	//sceneSectionWindowFlags |= ImGuiWindowFlags_AlwaysAutoResize;
	sceneSectionWindowFlags |= ImGuiWindowFlags_NoCollapse;
	sceneSectionWindowFlags |= ImGuiWindowFlags_NoBackground;
	sceneSectionWindowFlags |= ImGuiWindowFlags_NoDocking;
	sceneSectionWindowFlags |= ImGuiWindowFlags_NoSavedSettings;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("Scene Section");
	//ZERO_CLIENT_INFO("Scene Section \\/");

	ImVec2 availSize =  ImGui::GetContentRegionAvail();
	
	if (m_SceneWindowSize != (*(glm::vec2*)&availSize))
	{
		Zero::FramebufferSpecification framebufferSpec = Zero::Renderer2D::GetFramebuffer()->GetFramebufferSpecification();
		framebufferSpec.Width = (uint32_t)availSize.x;
		framebufferSpec.Height = (uint32_t)availSize.y;

		Zero::Renderer2D::GetFramebuffer()->SetFramebufferSpecification(framebufferSpec);


		float aspectRatio = availSize.x / availSize.y;
		m_CameraController.SetAspectRatio(aspectRatio);

		m_SceneWindowSize.x = availSize.x;
		m_SceneWindowSize.y = availSize.y;

	}
	auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
	auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
	auto viewportOffset = ImGui::GetWindowPos();

	m_ViewportBounds[0] = {viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
	m_ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

	

	ImVec2 uv0 = ImVec2(-1.0f, 1.0f); //Bottom-Left
	ImVec2 uv1 = ImVec2(0.0f, 0.0f);

	ImVec4 border_col = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
	ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

	ImGui::Image((void*)(Zero::Renderer2D::GetFramebuffer()->GetFramebufferTexID()), availSize, uv0, uv1, tint_col, border_col);
	ImGui::PopStyleVar();
	//ImGui::PopID();
	ImGui::End();
}

void Sandbox2D::OptionsSection(bool* show)
{
	//int currentId = 0;
	//Option section configuration.

	ImGuiWindowFlags optionSectionWindowFlags = 0;
	//optionSectionWindowFlags |= ImGuiWindowFlags_AlwaysAutoResize;
	optionSectionWindowFlags |= ImGuiWindowFlags_NoCollapse;
	optionSectionWindowFlags |= ImGuiWindowFlags_NoBackground;
	optionSectionWindowFlags |= ImGuiWindowFlags_NoDocking;
	optionSectionWindowFlags |= ImGuiWindowFlags_NoSavedSettings;


	ImGui::Begin("Option Section");	


	ImGui::ColorPicker4("Brush Color", m_CurrentBrush->BrushColor);
	ImGui::Text("Clear the shapes:");
	if (ImGui::Button("Clear"))
	{
		Zero::Renderer2D::ClearBuffer();
	}
	ImGui::SliderFloat("Brush Width", &m_CurrentBrush->BrushThickness, 0.2f, 1.0f, "%.3f", ImGuiSliderFlags_AlwaysClamp);

	uint32_t brushesInRow = 0;
	ImGui::Text("Brushes");
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

		//ImGui::PushID(currentId);
		int frame_padding = -1 + i;
		ImVec2 size = ImVec2(32.0f, 32.0f);
		ImVec2 uv0 = ImVec2(-1.0f, 1.0f); //Bottom-Left
		ImVec2 uv1 = ImVec2(0.0f, 0.0f);

		ImVec4 bg_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
		ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
		if (ImGui::ImageButton((void*)(intptr_t)(brushData->BrushTex->GetTextureID()), size, uv0, uv1, frame_padding, bg_col, tint_col))
		{
			m_CurrentBrush = brushData;
		}
		//currentId++;
		ImGui::SameLine();
		//ImGui::PopID();
		brushesInRow++;
	}
	ImGui::End();
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
	Zero::RenderCommand::SetClearColor(m_FramebufferClearColor);
	Zero::RenderCommand::Clear();

	Zero::Renderer::BeginScene(m_CameraController.GetCamera());
	Zero::Renderer2D::BeginScene(m_CameraController.GetCamera());

	
	Zero::FramebufferSpecification framebufferSpec = Zero::Renderer2D::GetFramebuffer()->GetFramebufferSpecification();

	/*
	float aspectRatio = (float)framebufferSpec.Width / (float)framebufferSpec.Height;
	m_CameraController.SetAspectRatio(aspectRatio);
	*/

	m_CameraController.OnUpdate(timestep);

	/*
	if (Zero::Input::IsKeyPressed(ZERO_MOUSE_BUTTON_1))
	{
		m_MouseHold = true;
	}
	else if (Zero::Input::IsKeyReleased(ZERO_MOUSE_BUTTON_1))
	{
		m_MouseHold = false;
	}
	*/
	
	m_MouseHold = ImGui::IsMouseDown(ImGuiMouseButton_Left);
	/*
	if (m_MouseHold)
	{
		ZERO_CLIENT_INFO("Left Mouse Button is Holded.");
	}
	*/
	
	
	/*
	auto mousePosPair = Zero::Input::GetMousePosNormalized(m_SceneWindowSize.x,
														   m_SceneWindowSize.y);
	m_MousePos = glm::vec3(mousePosPair.first, mousePosPair.second, 0);
	*/
	
	;

	auto temp = ImGui::GetMousePos();
	m_MousePos.x = temp.x;
	m_MousePos.y = temp.y;
	m_MousePos.z = 0.0f;

	m_MousePos.x -= m_ViewportBounds[0].x;
	m_MousePos.y -= m_ViewportBounds[0].y;

	
	glm::vec2 viewPortSize = m_ViewportBounds[1] - m_ViewportBounds[0];
	//m_MousePos.y = viewPortSize.y - m_MousePos.y;

	uint32_t mouseX = (uint32_t)m_MousePos.x;
	uint32_t mouseY = (uint32_t)m_MousePos.y;
	//ZERO_CLIENT_INFO("Mouse X: " + std::to_string(mouseX) + ", Mouse Y: " + std::to_string(mouseY));

	bool isMousePosInBounds = mouseX >= 0 && mouseY >= 0 && mouseX < viewPortSize.x && mouseY < viewPortSize.y;
	
	if (m_MouseHold && isMousePosInBounds)
	{
		
		//ZERO_CLIENT_INFO(Zero::Renderer2D::GetFramebuffer()->GetFramebufferDetails());
		
		glm::vec3 normalizedMousePos;
		normalizedMousePos.x = -1.0f + 2.0f * (m_MousePos.x/ framebufferSpec.Width);
		normalizedMousePos.y = 1.0f - 2.0f * (m_MousePos.y / (float)framebufferSpec.Height);
		normalizedMousePos.z = m_MousePos.z;
		glm::vec3 worldPos = ScreenToWorldPoint(normalizedMousePos);
		
		ZERO_CLIENT_INFO("World Position: " 
						  + std::to_string(worldPos.x) + ", " 
						  + std::to_string(worldPos.y) + ", " 
						  + std::to_string(worldPos.z));
		
		

		float distance = glm::distance(m_PreviousPoint, worldPos);
		float clearQuadVecDistance = 2 * m_QuadDrawMinDistance;

		
		if (distance >= clearQuadVecDistance && m_Points.size() == 1)
		{
			ZERO_CLIENT_INFO("Clearing points array");
			m_Points.clear();
		}
		else if (distance >= m_QuadDrawMinDistance)
		{
			m_Points.push_back(worldPos);
			glm::vec3 direction = glm::normalize(worldPos - m_PreviousPoint);
			m_PreviousPoint = worldPos;
			if (CreateQuad())
			{
				ZERO_CLIENT_INFO("Drawing Quad");
				//We are doing this to avoid showing vacant spaces between lines.
				m_Points.push_back(worldPos - direction * 0.1f);
			}

		}
		
		
	}	
	
	Zero::Renderer2D::UpdateFramebuffer();
	//std::string pixelInfo = "Pixel Color: " + Zero::RenderCommand::ReadPixel(mousePos.x, mousePos.y, framebufferSpec.Width, framebufferSpec.Height);
	//ZERO_CLIENT_INFO(pixelInfo);
	//Zero::RenderCommand::SetViewport(0, 0, framebufferSpec.Width, framebufferSpec.Height);


	Zero::RenderCommand::SetClearColor(m_MainWindowClearColor);
	Zero::RenderCommand::Clear();

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
	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDocking;
	windowFlags |= ImGuiWindowFlags_NoTitleBar;
	windowFlags |= ImGuiWindowFlags_NoCollapse;
	windowFlags |= ImGuiWindowFlags_NoResize;
	windowFlags |= ImGuiWindowFlags_NoMove;
	windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	windowFlags |= ImGuiWindowFlags_NoNavFocus;
	windowFlags |= ImGuiWindowFlags_NoBackground;
	
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("MainWindow", nullptr, windowFlags);
	ImGui::PopStyleVar(3);

	ImGuiID dockspaceID =  ImGui::GetID("MainWindowDockSpace");
	
	ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
	
	ImGui::End();

	SceneSection(nullptr);
	OptionsSection(nullptr);
	
}
bool Sandbox2D::OnWindowResized(Zero::WindowResizedEvent& event)
{
	//float aspectRatio = (float)event.GetWidth() / (float)event.GetHeight();
	//m_CameraController.SetAspectRatio(aspectRatio);
	return true;
}

bool Sandbox2D::OnKeyPressed(Zero::KeyPressedEvent& event)
{
	return false;
}

bool Sandbox2D::OnKeyTyped(Zero::KeyTypedEvent& event)
{
	return false;
}

bool Sandbox2D::OnMouseScrolled(Zero::MouseScrolledEvent& event)
{
	return false;
}

bool Sandbox2D::OnMouseClicked(Zero::MouseButtonClickedEvent& event)
{
	return false;
}
