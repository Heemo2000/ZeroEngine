#include "SandboxApp.h"
#include "backends/imgui_impl_opengl3.h"
#include <glm/gtc/type_ptr.hpp>

SandboxLayer::SandboxLayer() : Zero::Layer("SandboxLayer") 
{
	Zero::Renderer::Init();
	//m_Camera.reset(Zero::OrthographicCamera::Create(16.0f / 9.0f, 1.0f,glm::vec3(0.0f,0.0f,0.0f)));
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

void SandboxLayer::OnUpdate(Zero::Timestep timestep)
{
	Zero::RenderCommand::SetClearColor(m_ClearColor);
	Zero::RenderCommand::Clear();
	
	//Zero::Renderer::BeginScene(m_Camera);
	
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
	
	//m_Camera->SetPosition(m_CameraPosition);
	//m_Camera->SetRotation(m_CameraRotation);
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
	//m_Camera->SetAspectRatio(aspectRatio);
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
	//m_Camera->SetScale(m_Camera->GetScale() + event.GetScrolledY());
	return true;
}

bool SandboxLayer::OnMouseClicked(Zero::MouseButtonClickedEvent& event)
{	
	return true;
}


Zero::Application* Zero::CreateApplication()
{
	return new Sandbox();
}

/*---------------------Quad--------------------------*/
Quad::Quad(glm::vec3 worldPosition) : m_Transform(Zero::Transform(worldPosition)),m_Enabled(false)
{
	float quadVertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	unsigned int indices[] =
	{
		0,1,2,
		2,3,0
	};

	BufferLayout quadLayout =
	{
		{"a_Position",ShaderDataType::Float3}
	};

	m_QuadVA = Zero::VertexArray::Create();

	m_QuadVB.reset(Zero::VertexBuffer::Create(quadVertices, sizeof(quadVertices)));
	m_QuadVB->SetLayout(quadLayout);

	m_QuadIB.reset(Zero::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

	m_QuadVA->AddVertexBuffer(m_QuadVB);
	m_QuadVA->SetIndexBuffer(m_QuadIB);

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
			
			uniform vec4 u_Color;
			out vec4 outColor;
			void main()
			{
				outColor = u_Color;
			}
	)";

	m_Shader = Zero::Shader::Create("quad",quadVS, quadFS);
}

bool Quad::IsEnabled()
{
	return m_Enabled;
}

void Quad::DrawQuad()
{
	if (m_Enabled)
	{
		ZERO_CLIENT_TRACE("Rendering Quad");
		Zero::Renderer::Submit(m_Shader, m_QuadVA, m_Transform.GetTransformationMatrix());
	}
}

void Quad::SetEnabled(bool enabled)
{
	ZERO_CLIENT_TRACE("Quad enabled : {0}", enabled);
	this->m_Enabled = enabled;
}

void Quad::SetPosition(glm::vec3 position)
{
	this->m_Transform.SetPosition(position);
}

void Quad::SetScale(glm::vec3 scale)
{
	m_Transform.SetScale(scale);
}

void Quad::SetColor(glm::vec4 color)
{
	m_Shader->UploadData("u_Color", color);
}
