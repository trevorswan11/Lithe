#include "Sandbox2D.h"

#include "imgui/imgui.h"

#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = Lithe::Texture2D::Create("assets/textures/CheckerboardExample.png");
	m_MountainTexture = Lithe::Texture2D::Create("assets/textures/SmokeyMountains.jpg");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Lithe::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Lithe::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Lithe::RenderCommand::Clear();

	Lithe::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Lithe::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	Lithe::Renderer2D::DrawRotatedQuad({-1.0f, 0.0f }, 20.0f, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	
	Lithe::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f);
	Lithe::Renderer2D::DrawQuad({ 1.0f, 1.0f, -0.1f }, { 100.0f, 100.0f }, m_MountainTexture, 10.0f);
	
	Lithe::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Lithe::Event& e)
{
	m_CameraController.OnEvent(e);
}
