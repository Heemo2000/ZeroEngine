#include "Sandbox2D.h"
#include "backends/imgui_impl_opengl3.h"

Sandbox2D::Sandbox2D() : m_CameraController(Zero::OrthographicCameraController(16.0f/9.0f,false))
{
	Zero::Renderer::Init();
	Zero::Renderer2D::Init();

	m_CameraController = Zero::OrthographicCameraController(16.0f / 9.0f, false);

	m_ClearColor.r = 0.0f;
	m_ClearColor.g = 0.0f;
	m_ClearColor.b = 0.0f;
	m_ClearColor.a = 1.0f;

	Zero::MeshVertex v1;
	v1.Position = { -0.5f, -0.5f, 0.0f };
	v1.Color = {1.0f, 1.0f, 1.0f, 1.0f};

	Zero::MeshVertex v2;
	v2.Position = { 0.5f, -0.5f, 0.0f };
	v2.Color = { 1.0f, 1.0f, 1.0f, 1.0f };

	Zero::MeshVertex v3;
	v3.Position = { 0.5f,  0.5f, 0.0f };
	v3.Color = { 1.0f, 1.0f, 1.0f, 1.0f };

	Zero::MeshVertex v4;
	v4.Position = { -0.5f,  0.5f, 0.0f };
	v4.Color = { 1.0f, 1.0f, 1.0f, 1.0f };
	

	/*
	std::vector<uint32_t> indices =
	{
		0,1,2,
		2,3,0
	};
	*/
	
	m_Quad.reset(new Zero::Quad({v1,v2,v3,v4}));
	Zero::Renderer2D::AddQuadToBuffer(m_Quad.get());
}

void Sandbox2D::ToggleChangeVertices()
{
	ZERO_CLIENT_INFO("Changing vertices");

	m_Switch = !m_Switch;
	glm::vec3 secondPos = m_Quad->GetVertices()[1].Position;
	glm::vec3 thirdPos = m_Quad->GetVertices()[1].Position;
	if (m_Switch == true)
	{
		secondPos.y = -1.8f;
		thirdPos.y = 1.8f;
	}
	else
	{
		secondPos.y = -0.5f;
		thirdPos.y = 0.5f;
	}

	m_Quad->SetVertexPosition(secondPos, 1);
	m_Quad->SetVertexPosition(thirdPos, 2);

	ZERO_CLIENT_INFO("Vertices after updating");
	for (int i = 0; i < m_Quad->GetVertices().size(); i++)
	{
		auto position = m_Quad->GetVertices()[i].Position;
		std::string positionInStr = "(" + std::to_string(position.x) + "," + std::to_string(position.y) + "," + std::to_string(position.z) + ")";
		ZERO_CLIENT_INFO(positionInStr);
	}
	Zero::Renderer2D::UpdateQuad(m_Quad.get(), m_Quad->GetVertices());
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

void Sandbox2D::OnAttach()
{
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Zero::Timestep timestep)
{
	Zero::RenderCommand::SetClearColor(m_ClearColor);
	Zero::RenderCommand::Clear();

	Zero::Renderer::BeginScene(m_CameraController.GetCamera());
	Zero::Renderer2D::BeginScene(m_CameraController.GetCamera());

	m_CameraController.OnUpdate(timestep);
	m_ElapsedTime += timestep;
	if (m_ElapsedTime >= 1.0f)
	{
		ToggleChangeVertices();
		m_ElapsedTime = 0.0f;
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
	/*
	ImGui::Begin("Settings");
	ImGui::ShowDemoWindow(&m_Open);
	ImGui::End();
	*/
	
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
	auto mousePosPair = Zero::Input::GetMousePosNormalized();
	glm::vec3 mousePos;
	mousePos.x = mousePosPair.first;
	mousePos.y = mousePosPair.second;
	mousePos.z = 0;
	//ZERO_CLIENT_INFO("Mouse position :(" + std::to_string(mousePos.x) + "," + std::to_string(mousePos.y) + "," + std::to_string(mousePos.z) + ")");

	glm::vec3 worldPos = ScreenToWorldPoint(mousePos);
	ZERO_CLIENT_INFO("World position :(" + std::to_string(worldPos.x) + "," + std::to_string(worldPos.y) + "," + std::to_string(worldPos.z) + ")");
	
	return true;
}
