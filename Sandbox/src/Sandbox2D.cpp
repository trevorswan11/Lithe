#include "Sandbox2D.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	LI_PROFILE_FUNCTION();

	m_CheckerboardTexture = Lithe::Texture2D::Create("assets/textures/CheckerboardExample.png");
}

void Sandbox2D::OnDetach()
{
	LI_PROFILE_FUNCTION();

}

void Sandbox2D::OnUpdate(Lithe::Timestep ts)
{
	LI_PROFILE_FUNCTION();

	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	{
		LI_PROFILE_SCOPE("Renderer Prep");
		Lithe::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Lithe::RenderCommand::Clear();
	}

	{
		LI_PROFILE_SCOPE("Renderer Draw");
		Lithe::Renderer2D::BeginScene(m_CameraController.GetCamera());

		//Lithe::Renderer2D::DrawRotatedQuad({ -1.0f, 0.0f }, 20.0f, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		
		Lithe::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Lithe::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });

		Lithe::Renderer2D::DrawQuad({ -5.0f, -5.0f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f);
		Lithe::Renderer2D::DrawQuad({ -5.0f, -5.0f }, { 0.3f, 0.3f }, m_CheckerboardTexture, { 0.2f, 0.3f, 0.8f, 1.0f }, 120.0f);
		
		Lithe::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	LI_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Lithe::Event& e)
{
	m_CameraController.OnEvent(e);
}
