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
		    void main()
			{	
				v_Color = a_Color;			
				gl_Position = vec4(a_Position,1.0);
			}
		)";


	std::string bigSquareVS = R"(
			#version 460 core
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			out vec4 v_Color;
			
			vec3 offset = vec3(1.0,0.0,0.0);
			float scale = 1.2;
		    void main()
			{	
				v_Color = a_Color;			
				gl_Position = vec4((a_Position) * scale + offset,1.0);
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

	m_ClearColor = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
}

void SandboxLayer::OnUpdate()
{
	Zero::RenderCommand::SetClearColor(m_ClearColor);
	Zero::RenderCommand::Clear();

	Zero::Renderer::BeginScene();
	m_SmallSquareShader->Bind();

	Zero::Renderer::Submit(m_SmallSquareVA);

	m_BigSquareShader->Bind();

	Zero::Renderer::Submit(m_BigSquareVA);

	Zero::Renderer::EndScene();
}

void SandboxLayer::OnEvent(Zero::Event& event)
{

}

void SandboxLayer::OnImGuiRender()
{

}


Zero::Application* Zero::CreateApplication()
{
	return new Sandbox();
}
