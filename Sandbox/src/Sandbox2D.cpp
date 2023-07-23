#include "Sandbox2D.h"
#include "backends/imgui_impl_opengl3.h"

Sandbox2D::Sandbox2D() : m_CameraController(Zero::OrthographicCameraController(16.0f/9.0f,false))
{
	Zero::Renderer::Init();
	Zero::Renderer2D::Init();

	m_CameraController = Zero::OrthographicCameraController(16.0f / 9.0f, false);

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
	

	std::vector<uint32_t> indices =
	{
		0,1,2,
		2,3,0
	};

	Zero::Mesh mesh({v1,v2,v3,v4}, indices);
	Zero::Renderer2D::AddMeshToBuffer(mesh);
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
