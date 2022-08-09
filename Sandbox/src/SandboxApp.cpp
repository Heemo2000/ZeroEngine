#include "SandboxApp.h"

SandboxLayer::SandboxLayer() : Zero::Layer("SandboxLayer") 
{
	float smallSquareVertices[] =
	{
		-0.5f,-0.5f,0.0f,    0.0f,0.6f,0.0f,1.0f,      0.0f,1.0f,0.0f,
		0.0f,-0.5f,0.0f,     0.0f,0.4f,0.0f,1.0f,      0.0f,1.0f,0.0f,
		0.0f,0.5f,0.0f,	     0.0f,0.6f,0.0f,1.0f,      0.0f,1.0f,0.0f,
		-0.5f,0.5f,0.0f,     0.0f,0.4f,0.0f,1.0f,      0.0f,1.0f,0.0f
	};

	float bigSquareVertices[] =
	{
		-0.5f,-0.5f,0.0f,    1.0f,0.2f,0.0f,1.0f,      0.0f,1.0f,0.0f,
		0.5f,-0.5f,0.0f,     0.6f,0.2f,0.0f,1.0f,      0.0f,1.0f,0.0f,
		0.5f,0.5f,0.0f,	     1.0f,0.2f,0.0f,1.0f,      0.0f,1.0f,0.0f,
		-0.5f,0.5f,0.0f,     0.6f,0.2f,0.0f,1.0f,      0.0f,1.0f,0.0f
	};

	unsigned int indices[] =
	{
		0,1,2,
		0,2,3
	};

	BufferLayout squareLayout =
	{
	  {"a_Position",ShaderDataType::Float3},
	  {"a_Color",ShaderDataType::Float4},
	  {"a_Normal",ShaderDataType::Float3}
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
			layout(location = 2) in vec3 a_Normal;

			out vec4 v_Color;
			out vec3 v_Normal;
			out vec3 v_FragPosition;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_TransformationMatrix;
			
			vec4 cachedPos = vec4(0.0,0.0,0.0,1.0);
			void calculatePosition(in mat4 viewProjection,in mat4 transformationMatrix,in vec3 vertexPosition,out vec4 result)
			{
				result = viewProjection * transformationMatrix * vec4(vertexPosition,1.0);
			}

		    void main()
			{	
				v_Color = a_Color;
				v_Normal = a_Normal;
				calculatePosition(u_ViewProjection,u_TransformationMatrix,a_Position,cachedPos);
				v_FragPosition = cachedPos.xyz;
				gl_Position = cachedPos;
			}
		)";


	std::string bigSquareVS = R"(
			#version 460 core
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			layout(location = 2) in vec3 a_Normal;

			out vec4 v_Color;
			out vec3 v_Normal;
			out vec3 v_FragPosition;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_TransformationMatrix;
		    void main()
			{	
				v_Color = a_Color;
				v_Normal = a_Normal;			
				gl_Position = u_ViewProjection * u_TransformationMatrix * vec4((a_Position),1.0);
				v_FragPosition = gl_Position.xyz;
			}
		)";

	std::string fragmentSource = R"(
			#version 460 core

			out vec4 outColor;			

			in vec4 v_Color;
			in vec3 v_Normal;
			in vec3 v_FragPosition;
						
			struct Material
			{
				vec3 ambient;
				vec3 diffuse;
				vec3 specular;
			};
	
			struct Light
			{
				float ambientStrength;
				float diffuseStrength;
				float specularStrength;
			};

			uniform Material u_Material;
			uniform Light u_Light;
			uniform vec3 u_LightPosition;
			uniform int u_LightShininess;
			
			vec4 phongLight = vec4(1.0,1.0,1.0,1.0);
			
			void calculatePhongLightning(in Material material,in vec3 lightPosition,in int lightShininess,in Light light,
										 in vec3 normal,in vec3 fragmentPosition,
										 in vec3 viewPosition, out vec4 result)
			{
				vec3 ambientAmount = light.ambientStrength * material.ambient;
				
				vec3 lightDirection = normalize(fragmentPosition - lightPosition);
				vec3 normalizedNormal = normalize(normal);
				float diffuse = max(0,dot(normalizedNormal,lightDirection));
				
				vec3 diffuseAmount = light.diffuseStrength * material.diffuse;

				vec3 viewDirection = normalize(viewPosition - fragmentPosition);

				vec3 reflectDirection = reflect(-lightDirection,normalizedNormal);

				float specular = pow(max(0,dot(viewDirection,reflectDirection)),lightShininess);

				vec3 specularAmount = light.specularStrength * material.specular;
				
				result = vec4(ambientAmount + diffuseAmount + specularAmount,1.0);
			}

		    void main()
			{
				vec3 lightPosition = vec3(0,0,1);
				calculatePhongLightning(u_Material,u_LightPosition,u_LightShininess,u_Light,v_Normal,v_FragPosition,u_LightShininess,phongLight);
				outColor = phongLight * v_Color;
			}
		)";


	m_SmallSquareShader.reset(Zero::Shader::Create(smallSquareVS, fragmentSource));

	m_BigSquareShader.reset(Zero::Shader::Create(bigSquareVS, fragmentSource));

	m_Camera.reset(Zero::OrthographicCamera::Create(16.0f/9.0f,1.0f, m_CameraPosition));
	m_ClearColor = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);

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

	m_SmallSquareShader->Bind();

	m_SmallSquareShader->UploadData("u_Material.ambient", m_LightColor);
	m_SmallSquareShader->UploadData("u_Material.diffuse", m_LightColor);
	m_SmallSquareShader->UploadData("u_Material.specular", m_LightColor);

	m_SmallSquareShader->UploadData("u_Light.ambientStrength", 0.1f);
	m_SmallSquareShader->UploadData("u_Light.diffuseStrength", 1.0f);
	m_SmallSquareShader->UploadData("u_Light.specularStrength", std::sin(m_ElapsedTime * 3.141f) * 20.0f + 20.0f);
	m_SmallSquareShader->UploadData("u_LightShininess", 128);
	m_SmallSquareShader->UploadData("u_LightPosition", m_Camera->GetPosition());

	Zero::Renderer::Submit(m_SmallSquareShader, m_SmallSquareVA,m_SmallSquareTransform.GetTransformationMatrix());
	
#pragma endregion SmallSquareControl

	m_BigSquareShader->Bind();

	m_BigSquareShader->UploadData("u_Material.ambient", m_LightColor);
	m_BigSquareShader->UploadData("u_Material.diffuse", m_LightColor);
	m_BigSquareShader->UploadData("u_Material.specular", m_LightColor);

	m_BigSquareShader->UploadData("u_Light.ambientStrength", 0.1f);
	m_BigSquareShader->UploadData("u_Light.diffuseStrength", 1.0f);
	m_BigSquareShader->UploadData("u_Light.specularStrength", std::cos(m_ElapsedTime * 3.141f) * 20.0f + 20.0f);
	m_BigSquareShader->UploadData("u_LightShininess", 128);
	m_BigSquareShader->UploadData("u_LightPosition", m_Camera->GetPosition());

	Zero::Renderer::Submit(m_BigSquareShader,m_BigSquareVA, m_BigSquareTransform.GetTransformationMatrix());
	
	m_ElapsedTime += timestep;
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
