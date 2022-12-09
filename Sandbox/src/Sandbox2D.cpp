#include "Sandbox2D.h"

Sandbox2D::Sandbox2D()
{
	Zero::Renderer::Init();
	m_Camera.reset(Zero::OrthographicCamera::Create(16.0f / 9.0f, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f)));
	std::vector<float> quadVertices =
	{
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	std::vector<uint32_t> indices =
	{
		0,1,2,
		2,3,0
	};

	m_QuadInstances = new Zero::InstanceManager(quadVertices, indices, m_N * m_N);
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

	Zero::Renderer::BeginScene(m_Camera);

#pragma region CameraControl
	if (Zero::Input::IsKeyPressed(ZERO_KEY_W))
	{
		m_CameraPosition.y += m_CameraMoveSpeed * timestep.GetDeltaTimeInSec();
	}

	else if (Zero::Input::IsKeyPressed(ZERO_KEY_S))
	{
		m_CameraPosition.y -= m_CameraMoveSpeed * timestep.GetDeltaTimeInSec();
	}

	if (Zero::Input::IsKeyPressed(ZERO_KEY_A))
	{
		m_CameraPosition.x -= m_CameraMoveSpeed * timestep.GetDeltaTimeInSec();
	}

	else if (Zero::Input::IsKeyPressed(ZERO_KEY_D))
	{
		m_CameraPosition.x += m_CameraMoveSpeed * timestep.GetDeltaTimeInSec();
	}

	if (Zero::Input::IsKeyPressed(ZERO_KEY_Q))
	{
		m_CameraRotation += m_CameraRotationSpeed * timestep.GetDeltaTimeInSec();
	}

	else if (Zero::Input::IsKeyPressed(ZERO_KEY_E))
	{
		m_CameraRotation -= m_CameraRotationSpeed * timestep.GetDeltaTimeInSec();
	}

	m_Camera->SetPosition(m_CameraPosition);
	m_Camera->SetRotation(m_CameraRotation);
#pragma endregion CameraControl

	m_QuadInstances->SetOrigin(m_Origin);
	glm::vec3 scale = glm::vec3(1.0f);

	uint32_t instanceNo = 0;
	for (int y = 0; y < m_N; y++)
	{
		for (int x = 0; x < m_N; x++)
		{
			if (instanceNo % 2 == 0)
			{
				m_QuadInstances->SetColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else
			{
				m_QuadInstances->SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
			}
			m_QuadInstances->SetScale(scale);
			glm::vec3 offSet = glm::vec3(x * scale.x, -y * scale.y, 0.0f);
			m_QuadInstances->SetOffset(instanceNo, offSet);
			instanceNo++;
		}
	}
	m_QuadInstances->DrawInstances();
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
}

void Sandbox2D::OnImGuiRender()
{
}

bool Sandbox2D::OnWindowResized(Zero::WindowResizedEvent& event)
{
	float aspectRatio = (float)event.GetWidth() / (float)event.GetHeight();
	m_Camera->SetAspectRatio(aspectRatio);
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
	m_Camera->SetScale(m_Camera->GetScale() + event.GetScrolledY());
	return true;
}

bool Sandbox2D::OnMouseClicked(Zero::MouseButtonClickedEvent& event)
{
	return true;
}
