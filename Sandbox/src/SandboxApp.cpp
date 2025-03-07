#include <Lithe.h>

#include "imgui/imgui.h"

// using namespace Lithe; // Makes implementation much easier, not done here for clarity

class ExampleLayer : public Lithe::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Lithe::VertexArray::Create());

		// Vertex Buffer
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Lithe::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Lithe::VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer.reset(Lithe::VertexBuffer::Create(vertices, sizeof(vertices)));

		Lithe::BufferLayout layout = {
			{ Lithe::ShaderDataType::Float3, "a_Position" },
			{ Lithe::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		// Index Buffer
		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Lithe::IndexBuffer> indexBuffer;
		indexBuffer.reset(Lithe::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Lithe::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			0.75f, -0.75f, 0.0f,
			0.75f, 0.75f, 0.0f,
			-0.75f, 0.75f, 0.0f,
		};

		std::shared_ptr<Lithe::VertexBuffer> squareVB;
		squareVB.reset(Lithe::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Lithe::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Lithe::IndexBuffer> squareIB;
		squareIB.reset(Lithe::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		// Shader source code to use -- Use R"()" for easy multi-line strings
		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;	

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;				
			in vec4 v_Color;	

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Lithe::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;				

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new Lithe::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate() override
	{
		if (Lithe::Input::IsKeyPressed(LI_KEY_W))
			m_CameraPosition.y += m_CameraMoveSpeed;
		else if (Lithe::Input::IsKeyPressed(LI_KEY_S))
			m_CameraPosition.y -= m_CameraMoveSpeed;

		if (Lithe::Input::IsKeyPressed(LI_KEY_A))
			m_CameraPosition.x -= m_CameraMoveSpeed;
		else if (Lithe::Input::IsKeyPressed(LI_KEY_D))
			m_CameraPosition.x += m_CameraMoveSpeed;

		if (Lithe::Input::IsKeyPressed(LI_KEY_Q))
			m_CameraRotation -= m_CameraRotationSpeed;
		else if (Lithe::Input::IsKeyPressed(LI_KEY_E))
			m_CameraRotation += m_CameraRotationSpeed;

		if (Lithe::Input::IsKeyPressed(LI_KEY_R))
		{
			m_CameraPosition.x = 0.0f;
			m_CameraPosition.y = 0.0f;
			m_CameraRotation = 0.0f;
		}

		Lithe::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Lithe::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Lithe::Renderer::BeginScene(m_Camera);

		Lithe::Renderer::Submit(m_BlueShader, m_SquareVA);
		Lithe::Renderer::Submit(m_Shader, m_VertexArray);
			  
		Lithe::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{

	}

	void OnEvent(Lithe::Event& event) override
	{
	}

private:
	std::shared_ptr<Lithe::Shader> m_Shader;
	std::shared_ptr<Lithe::VertexArray> m_VertexArray;

	std::shared_ptr<Lithe::VertexArray> m_SquareVA;
	std::shared_ptr<Lithe::Shader> m_BlueShader;

	Lithe::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 0.01f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 2.0f;
};

class Sandbox : public Lithe::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		Lithe::Application::GetWindow().SetVSync(true);
	}

	~Sandbox()
	{

	}
};

Lithe::Application* Lithe::CreateApplication()
{
	return new Sandbox();
}