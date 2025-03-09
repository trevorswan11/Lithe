#include <Lithe.h>
#include <Lithe/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

// using namespace Lithe; // Makes implementation much easier, not done here for clarity

class ExampleLayer : public Lithe::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f, true)
	{
		m_VertexArray = Lithe::VertexArray::Create();

		// Vertex Buffer
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Lithe::Ref<Lithe::VertexBuffer> vertexBuffer;
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
		Lithe::Ref<Lithe::IndexBuffer> indexBuffer;
		indexBuffer.reset(Lithe::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA = Lithe::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
			- 0.5f, 0.5f, 0.0f, 0.0f, 1.0f
		};

		Lithe::Ref<Lithe::VertexBuffer> squareVB;
		squareVB.reset(Lithe::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Lithe::ShaderDataType::Float3, "a_Position" },
			{ Lithe::ShaderDataType::Float2, "a_TexCoord" }
		});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Lithe::Ref<Lithe::IndexBuffer> squareIB;
		squareIB.reset(Lithe::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		// Shader source code to use -- Use R"()" for easy multi-line strings
		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;	

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

		m_Shader = Lithe::Shader::Create("vertexShader", vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;	

			uniform vec3 u_Color;			

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader = Lithe::Shader::Create("flatColorShader", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Lithe::Texture2D::Create("assets/textures/CheckerboardExample.png");
		m_YellowBalloonTexture = Lithe::Texture2D::Create("assets/textures/BTD6_YellowBalloon.png");
		
		std::dynamic_pointer_cast<Lithe::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Lithe::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Lithe::Timestep ts) override
	{
		// Update
		m_CameraController.OnUpdate(ts);

		// Render
		Lithe::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Lithe::RenderCommand::Clear();

		Lithe::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Lithe::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Lithe::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);
		
		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Lithe::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Lithe::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_YellowBalloonTexture->Bind();
		Lithe::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Triangle
		//Lithe::Renderer::Submit(m_Shader, m_VertexArray);
			  
		Lithe::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Lithe::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

private:
	Lithe::ShaderLibrary m_ShaderLibrary;
	Lithe::Ref<Lithe::Shader> m_Shader;
	Lithe::Ref<Lithe::VertexArray> m_VertexArray;

	Lithe::Ref<Lithe::VertexArray> m_SquareVA;
	Lithe::Ref<Lithe::Shader> m_FlatColorShader;

	Lithe::Ref<Lithe::Texture2D> m_Texture, m_YellowBalloonTexture;

	Lithe::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Lithe::Application
{
public:
	Sandbox()
	{
		Lithe::Application::GetWindow().SetVSync(true);

		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}
};

Lithe::Application* Lithe::CreateApplication()
{
	return new Sandbox();
}