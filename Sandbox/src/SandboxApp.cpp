#include "SandboxApp.h"
#include "backends/imgui_impl_opengl3.h"
#include <glm/gtc/type_ptr.hpp>

SandboxLayer::SandboxLayer() : Zero::Layer("SandboxLayer") 
{
	float smallSquareVertices[] =
	{
		-0.5f,-0.5f,0.0f,
		0.0f,-0.5f,0.0f, 
		0.0f,0.5f,0.0f,	 
		-0.5f,0.5f,0.0f
	};

	float bigSquareVertices[] =
	{
		-0.5f,-0.5f,0.0f,    0.0f,0.0f,
		0.5f,-0.5f,0.0f,     1.0f,0.0f,
		0.5f,0.5f,0.0f,	     1.0f,1.0f,
		-0.5f,0.5f,0.0f,     0.0f,1.0f
	};

	unsigned int indices[] =
	{
		0,1,2,
		0,2,3
	};

	BufferLayout smallSquareLayout =
	{
		{"a_Position",ShaderDataType::Float3}
	};

	BufferLayout bigSquareLayout =
	{
	  {"a_Position",ShaderDataType::Float3},
	  {"a_TexCoord",ShaderDataType::Float2}
	};

	m_SmallSquareVA.reset(Zero::VertexArray::Create());

	m_smallSquareVBO.reset(Zero::VertexBuffer::Create(smallSquareVertices, sizeof(smallSquareVertices)));
	m_smallSquareVBO->SetLayout(smallSquareLayout);

	m_IndexBuffer.reset(Zero::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

	m_SmallSquareVA->AddVertexBuffer(m_smallSquareVBO);
	m_SmallSquareVA->SetIndexBuffer(m_IndexBuffer);

	m_BigSquareVA.reset(Zero::VertexArray::Create());

	m_BigSquareVBO.reset(Zero::VertexBuffer::Create(bigSquareVertices, sizeof(bigSquareVertices)));
	m_BigSquareVBO->SetLayout(bigSquareLayout);

	m_BigSquareVA->AddVertexBuffer(m_BigSquareVBO);
	m_BigSquareVA->SetIndexBuffer(m_IndexBuffer);


	std::string smallSquareVS = R"(
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


	std::string bigSquareVS = R"(
			#version 460 core
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			out vec2 v_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_TransformationMatrix;
		    void main()
			{	
				v_TexCoord = a_TexCoord;			
				gl_Position = u_ViewProjection * u_TransformationMatrix * vec4(a_Position,1.0);
			}
		)";


	std::string smallSquareFS = R"(
			#version 460 core
			
			out vec4 outColor;

			uniform vec4 u_Color;
			void main()
			{
				outColor = u_Color;
			}
	)";


	std::string bigSquareFS = R"(
			#version 460 core
			in vec2 v_TexCoord;

			uniform sampler2D texUnit;
			out vec4 outColor;

		    void main()
			{
				outColor = texture(texUnit,v_TexCoord);
			}
		)";

	m_SmallSquareShader.reset(Zero::Shader::Create(smallSquareVS, smallSquareFS));

	m_BigSquareShader.reset(Zero::Shader::Create(bigSquareVS, bigSquareFS));

	m_Camera.reset(Zero::OrthographicCamera::Create(16.0f/9.0f,1.0f, m_CameraPosition));
	m_ClearColor = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);

	m_BigSquareTexture.reset(Zero::Texture::Create("F://Projects_and_program_files/ZeroEngine/texture/logo.jpg",0));
	m_BigSquareTransform.SetScale(glm::vec3(1.2f, 1.2f, 1.2f));
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

#pragma region SmallSquareControl

	if (Zero::Input::IsKeyPressed(ZERO_KEY_I))
	{
		m_SmallSquarePosition.y += m_SmallSquareMoveSpeed * timestep.GetDeltaTimeInSec();
	}

	else if (Zero::Input::IsKeyPressed(ZERO_KEY_K))
	{
		m_SmallSquarePosition.y -= m_SmallSquareMoveSpeed * timestep.GetDeltaTimeInSec();
	}

	if (Zero::Input::IsKeyPressed(ZERO_KEY_J))
	{
		m_SmallSquarePosition.x -= m_SmallSquareMoveSpeed * timestep.GetDeltaTimeInSec();
	}

	else if (Zero::Input::IsKeyPressed(ZERO_KEY_L))
	{
		m_SmallSquarePosition.x += m_SmallSquareMoveSpeed * timestep.GetDeltaTimeInSec();
	}

	if (Zero::Input::IsKeyPressed(ZERO_KEY_U))
	{
		m_SmallSquareRotation += m_SmallSquareRotationSpeed * timestep.GetDeltaTimeInSec();
	}

	else if (Zero::Input::IsKeyPressed(ZERO_KEY_O))
	{
		m_SmallSquareRotation -= m_SmallSquareRotationSpeed * timestep.GetDeltaTimeInSec();
	}

	m_SmallSquareTransform.SetPosition(m_SmallSquarePosition);
	m_SmallSquareTransform.SetRotation(m_SmallSquareRotation);
	
	Zero::Renderer::Submit(m_SmallSquareShader, m_SmallSquareVA,m_SmallSquareTransform.GetTransformationMatrix());
	
#pragma endregion SmallSquareControl

	m_SmallSquareShader->UploadData("u_Color", m_SmallSquareColor);
	
	m_BigSquareTexture->Bind();
	Zero::Renderer::Submit(m_BigSquareShader,m_BigSquareVA, m_BigSquareTransform.GetTransformationMatrix());
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
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Small square color",glm::value_ptr(m_SmallSquareColor));
	ImGui::End();
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
