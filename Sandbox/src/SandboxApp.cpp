#include "SandboxApp.h"

SandboxLayer::SandboxLayer() : Zero::Layer("SandboxLayer") 
{
	float smallSquareVertices[] =
	{
		-0.5f,-0.5f,0.0f,    0.0f,0.2f,0.0f,1.0f,
		0.0f,-0.5f,0.0f,     0.0f,0.2f,0.0f,1.0f,
		0.0f,0.5f,0.0f,	     0.0f,0.2f,0.0f,1.0f,
		-0.5f,0.5f,0.0f,     0.0f,0.2f,0.0f,1.0f
	};

	float bigSquareVertices[] =
	{
		-0.5f,-0.5f,0.0f,    0.2f,0.2f,0.0f,1.0f,
		0.5f,-0.5f,0.0f,     0.2f,0.2f,0.0f,1.0f,
		0.5f,0.5f,0.0f,	     0.2f,0.2f,0.0f,1.0f,
		-0.5f,0.5f,0.0f,     0.2f,0.2f,0.0f,1.0f
	};

	unsigned int indices[] =
	{
		0,1,2,
		0,2,3
	};

	BufferLayout squareLayout =
	{
	  {"a_Position",ShaderDataType::Float3},
	  {"a_Color",ShaderDataType::Float4}
	};

	m_SmallSquareVA.reset(Zero::VertexArray::Create());

	m_smallSquareVBO.reset(Zero::VertexBuffer::Create(smallSquareVertices, sizeof(smallSquareVertices)));
	m_smallSquareVBO->SetLayout(squareLayout);

	m_IndexBuffer.reset(Zero::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

	m_SmallSquareVA->AddVertexBuffer(m_smallSquareVBO);
	m_SmallSquareVA->SetIndexBuffer(m_IndexBuffer);

	m_BigSquareVA.reset(Zero::VertexArray::Create());

	m_BigSquareVBO.reset(Zero::VertexBuffer::Create(bigSquareVertices, sizeof(bigSquareVertices)));
	m_BigSquareVBO->SetLayout(squareLayout);

	m_BigSquareVA->AddVertexBuffer(m_BigSquareVBO);
	m_BigSquareVA->SetIndexBuffer(m_IndexBuffer);


	std::string smallSquareVS = R"(
			#version 460 core
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			out vec4 v_Color;

			uniform mat4 viewProjection;
		    void main()
			{	
				v_Color = a_Color;			
				gl_Position = viewProjection * vec4(a_Position,1.0);
			}
		)";


	std::string bigSquareVS = R"(
			#version 460 core
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			out vec4 v_Color;
			
			uniform mat4 viewProjection;
			vec3 offset = vec3(1.0,0.0,0.0);
			float scale = 1.2;
		    void main()
			{	
				v_Color = a_Color;			
				gl_Position = viewProjection * vec4((a_Position) * scale + offset,1.0);
			}
		)";

	std::string fragmentSource = R"(
			#version 460 core
			
			in vec4 v_Color;
			out vec4 outColor;
		    void main()
			{
				outColor = v_Color;
			}
		)";


	m_SmallSquareShader.reset(Zero::Shader::Create(smallSquareVS, fragmentSource));

	m_BigSquareShader.reset(Zero::Shader::Create(bigSquareVS, fragmentSource));

	m_Camera.reset(Zero::OrthographicCamera::Create(16.0f/9.0f,1.0f, m_CameraPosition));
	m_ClearColor = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
}

void SandboxLayer::OnUpdate(Zero::Timestep timestep)
{
	Zero::RenderCommand::SetClearColor(m_ClearColor);
	Zero::RenderCommand::Clear();
	
	Zero::Renderer::BeginScene(m_Camera);
	
	if (Zero::Input::IsKeyPressed(ZERO_KEY_W))
	{
		m_CameraPosition.y += m_CameraMoveSpeed * timestep.GetFixedDeltaTimeInSec();
	}

	else if (Zero::Input::IsKeyPressed(ZERO_KEY_S))
	{
		m_CameraPosition.y -= m_CameraMoveSpeed * timestep.GetFixedDeltaTimeInSec();
	}

	if (Zero::Input::IsKeyPressed(ZERO_KEY_A))
	{
		m_CameraPosition.x -= m_CameraMoveSpeed * timestep.GetFixedDeltaTimeInSec();
	}

	else if (Zero::Input::IsKeyPressed(ZERO_KEY_D))
	{
		m_CameraPosition.x += m_CameraMoveSpeed * timestep.GetFixedDeltaTimeInSec();
	}

	if (Zero::Input::IsKeyPressed(ZERO_KEY_Q))
	{
		m_CameraRotation += m_CameraRotationSpeed * timestep.GetFixedDeltaTimeInSec();
	}

	else if (Zero::Input::IsKeyPressed(ZERO_KEY_E))
	{
		m_CameraRotation -= m_CameraRotationSpeed * timestep.GetFixedDeltaTimeInSec();
	}

	m_Camera->SetPosition(m_CameraPosition);
	m_Camera->SetRotation(m_CameraRotation);

	Zero::Renderer::Submit(m_SmallSquareShader,m_SmallSquareVA);

	Zero::Renderer::Submit(m_BigSquareShader,m_BigSquareVA);

	Zero::Renderer::EndScene();
}

void SandboxLayer::OnEvent(Zero::Event& event)
{
	Zero::EventDispatcher eventDispatcher(event);
	eventDispatcher.Dispatch<Zero::WindowResizedEvent>(ZERO_BIND_EVENT_FN(SandboxLayer::OnWindowResized));
	eventDispatcher.Dispatch<Zero::KeyPressedEvent>(ZERO_BIND_EVENT_FN(SandboxLayer::OnKeyPressed));
	eventDispatcher.Dispatch<Zero::KeyTypedEvent>(ZERO_BIND_EVENT_FN(SandboxLayer::OnKeyTyped));
	eventDispatcher.Dispatch<Zero::MouseScrolledEvent>(ZERO_BIND_EVENT_FN(SandboxLayer::OnMouseScrolled));
	
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


Zero::Application* Zero::CreateApplication()
{
	return new Sandbox();
}
