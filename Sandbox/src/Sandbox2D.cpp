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

	m_BrushColor[0] = 1.0f;
	m_BrushColor[1] = 1.0f;
	m_BrushColor[2] = 1.0f;
	m_BrushColor[3] = 1.0f;

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

		float height = m_BrushThickness;

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

		glm::vec4 vertexColor = glm::vec4(m_BrushColor[0], m_BrushColor[1], m_BrushColor[2], m_BrushColor[3]);
		Zero::MeshVertex v1;
		v1.Position = point1;
		v1.Color = vertexColor;

		Zero::MeshVertex v2;
		v2.Position = point2;
		v2.Color = vertexColor;

		Zero::MeshVertex v3;
		v3.Position = point3;
		v3.Color = vertexColor;

		Zero::MeshVertex v4;
		v4.Position = point4;
		v4.Color = vertexColor;

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
	
	if (m_MouseHold)
	{
		
		auto mousePosPair = Zero::Input::GetMousePosNormalized();
		glm::vec3 mousePos;
		mousePos.x = mousePosPair.first;
		mousePos.y = mousePosPair.second;
		mousePos.z = 0;

		glm::vec3 worldPos = ScreenToWorldPoint(mousePos);

		float distance = glm::distance(m_PreviousPoint, worldPos);
		float clearQuadVecDistance = 2 * m_QuadDrawMinDistance;
		
		if (distance >= clearQuadVecDistance && m_Points.size() == 1)
		{
			m_Points.clear();
		}
		else if (distance >= m_QuadDrawMinDistance)
		{
			m_Points.push_back(worldPos);
			glm::vec3 direction = glm::normalize(worldPos - m_PreviousPoint);
			m_PreviousPoint = worldPos;
			if (CreateQuad())
			{
				//We are doing this to avoid showing vacant spaces between lines.
				m_Points.push_back(worldPos - direction * 0.1f);
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
	ImGuiWindowFlags windowFlags = 0;
	windowFlags |= ImGuiWindowFlags_NoResize;
	ImGui::Begin("Settings",&m_Open, windowFlags);
	ImGui::ColorPicker4("Brush Color :", m_BrushColor);
	ImGui::Text("Clear the shapes:");
	if (ImGui::Button("Clear"))
	{
		Zero::Renderer2D::ClearBuffer();
	}
	ImGui::SliderFloat("Brush Width", &m_BrushThickness, 0.2f, 1.0f,"%.3f", ImGuiSliderFlags_AlwaysClamp);
	ImGui::End();
	ImGui::ShowDemoWindow(&m_Open);
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
