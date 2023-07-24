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

bool Sandbox2D::CreateQuad()
{
	if (m_Points.size() == 2)
	{
		//Calculate points in clockwise order.

		float height = 0.5f;
		glm::vec3 point1 = m_Points[0] - glm::vec3(0.0f, height / 2.0f, 0.0f);
		glm::vec3 point2 = m_Points[0] + glm::vec3(0.0f, height / 2.0f, 0.0f);
		glm::vec3 point3 = m_Points[1] + glm::vec3(0.0f, height / 2.0f, 0.0f);
		glm::vec3 point4 = m_Points[1] - glm::vec3(0.0f, height / 2.0f, 0.0f);

		Zero::MeshVertex v1;
		v1.Position = point1;
		v1.Color = glm::vec4(1.0f);

		Zero::MeshVertex v2;
		v2.Position = point2;
		v2.Color = glm::vec4(1.0f);

		Zero::MeshVertex v3;
		v3.Position = point3;
		v3.Color = glm::vec4(1.0f);

		Zero::MeshVertex v4;
		v4.Position = point4;
		v4.Color = glm::vec4(1.0f);

		Zero::Ref<Zero::Quad> quad;
		quad.reset(new Zero::Quad({ v1,v2,v3,v4 }));

		Zero::Renderer2D::AddQuadToBuffer(quad.get());
		m_Points.clear();

		return true;
	}

	return false;
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
	
	if (Zero::Input::IsMouseButtonPressed(ZERO_MOUSE_BUTTON_LEFT))
	{
		m_MouseHold = true;
	}
	else if(Zero::Input::IsMouseButtonReleased(ZERO_MOUSE_BUTTON_LEFT))
	{
		m_MouseHold = false;
	}
	
	float minDistance = 2.0f;
	auto mousePosPair = Zero::Input::GetMousePosNormalized();
	glm::vec3 mousePos;
	mousePos.x = mousePosPair.first;
	mousePos.y = mousePosPair.second;
	mousePos.z = 0;

	glm::vec3 worldPos = ScreenToWorldPoint(mousePos);

	if (m_MouseHold)
	{
		float distance = glm::distance(previousPoint, worldPos);
		if (distance >= minDistance)
		{
			m_Points.push_back(worldPos);
			if (CreateQuad())
			{
				previousPoint = worldPos;
			}
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

	return true;
}
