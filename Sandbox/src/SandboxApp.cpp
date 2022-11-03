#include "SandboxApp.h"
#include "backends/imgui_impl_opengl3.h"
#include <glm/gtc/type_ptr.hpp>

SandboxLayer::SandboxLayer() : Zero::Layer("SandboxLayer") 
{
	m_Camera.reset(Zero::OrthographicCamera::Create(16.0f / 9.0f, 1.0f,glm::vec3(0.0f,0.0f,0.0f)));
	//m_Quads = std::make_shared<std::vector<Zero::Ref<Quad>>>();
}

void SandboxLayer::OnUpdate(Zero::Timestep timestep)
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
	
	
	for (auto i = m_Quads.begin(); i != m_Quads.end(); i++)
	{
		(*i)->DrawQuad();
	}
	Zero::Renderer::EndScene();
}

void SandboxLayer::OnEvent(Zero::Event& event)
{
	Zero::EventDispatcher eventDispatcher(event);
	eventDispatcher.Dispatch<Zero::WindowResizedEvent>(ZERO_BIND_EVENT_FN(SandboxLayer::OnWindowResized));
	eventDispatcher.Dispatch<Zero::KeyPressedEvent>(ZERO_BIND_EVENT_FN(SandboxLayer::OnKeyPressed));
	eventDispatcher.Dispatch<Zero::KeyTypedEvent>(ZERO_BIND_EVENT_FN(SandboxLayer::OnKeyTyped));
	eventDispatcher.Dispatch<Zero::MouseScrolledEvent>(ZERO_BIND_EVENT_FN(SandboxLayer::OnMouseScrolled));	
	eventDispatcher.Dispatch<Zero::MouseButtonClickedEvent>(ZERO_BIND_EVENT_FN(SandboxLayer::OnMouseClicked));
}


void SandboxLayer::OnImGuiRender()
{
}

bool SandboxLayer::OnWindowResized(Zero::WindowResizedEvent& event)
{
	float aspectRatio = (float)event.GetWidth() / (float)event.GetHeight();
	m_Camera->SetAspectRatio(aspectRatio);
	return true;
}

bool SandboxLayer::OnKeyPressed(Zero::KeyPressedEvent& event)
{
	return true;
}

bool SandboxLayer::OnKeyTyped(Zero::KeyTypedEvent& event)
{
	return true;
}

bool SandboxLayer::OnMouseScrolled(Zero::MouseScrolledEvent& event)
{
	m_Camera->SetScale(m_Camera->GetScale() + event.GetScrolledY());
	return true;
}

bool SandboxLayer::OnMouseClicked(Zero::MouseButtonClickedEvent& event)
{
	
	m_Quads.push_back(std::make_shared<Quad>(m_Camera->GetPosition()));
	return true;
}


Zero::Application* Zero::CreateApplication()
{
	return new Sandbox();
}

/*---------------------Quad--------------------------*/
Quad::Quad(glm::vec3 worldPosition) : m_Transform(Zero::Transform(worldPosition))
{
	float quadVertices[] =
	{
		-0.5f,-0.25f,0.0f,
		0.0f,-0.25f,0.0f,
		0.0f,0.25f,0.0f,
		-0.5f,0.25f,0.0f
	};

	unsigned int indices[] =
	{
		0,1,2,
		0,2,3
	};

	BufferLayout quadLayout =
	{
		{"a_Position",ShaderDataType::Float3}
	};

	m_VertexArray.reset(Zero::VertexArray::Create());

	m_VertexBuffer.reset(Zero::VertexBuffer::Create(quadVertices, sizeof(quadVertices)));
	m_VertexBuffer->SetLayout(quadLayout);

	m_IndexBuffer.reset(Zero::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

	m_VertexArray->AddVertexBuffer(m_VertexBuffer);
	m_VertexArray->SetIndexBuffer(m_IndexBuffer);

	std::string quadVS = R"(
			#version 460 core
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_TransformationMatrix;
			
			vec4 cachedPos = vec4(0.0,0.0,0.0,1.0);
			
			void calculatePosition(in mat4 viewProjection,in mat4 transformationMatrix,in vec3 vertexPosition,out vec4 result)
			{
				result = viewProjection * transformationMatrix * vec4(vertexPosition,1.0);
			}

		    void main()
			{	
				calculatePosition(u_ViewProjection,u_TransformationMatrix,a_Position,cachedPos);
				gl_Position = cachedPos;
			}
		)";


	std::string quadFS = R"(
			#version 460 core
			
			out vec4 outColor;
			void main()
			{
				outColor = vec4(1.0f,1.0f,1.0,1.0f);
			}
	)";

	m_Shader.reset(Zero::Shader::Create(quadVS, quadFS));
}

void Quad::DrawQuad()
{
	ZERO_CLIENT_TRACE("Rendering Quad...");
	Zero::Renderer::Submit(m_Shader, m_VertexArray, m_Transform.GetTransformationMatrix());
}
