#include "Sandbox2D.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
}

Sandbox2D::Sandbox2D(Lithe::OrthographicCameraController& camera)
	: Layer("Sandbox2D"), m_CameraController(camera)
{
}

void Sandbox2D::OnAttach()
{
	LI_PROFILE_FUNCTION();

	m_CheckerboardTexture = Lithe::Texture2D::Create("assets/textures/CheckerboardExample.png");
	m_CameraController.SetZoomLevel(5.0f);
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
	Lithe::Renderer2D::ResetStats();
	{
		LI_PROFILE_SCOPE("Sandbox2D Renderer Prep");
		Lithe::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Lithe::RenderCommand::Clear();
	}

	{
		LI_PROFILE_SCOPE("Sandbox2D Renderer Draw");

		static float rotation = 0.0f;
		rotation += ts * 1.0f;

		Lithe::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Lithe::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f);
		
		Lithe::Renderer2D::DrawRotatedQuad({ -1.0f, -3.0f, 0.2f }, glm::radians(20.0f), { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Lithe::Renderer2D::DrawQuad({ 0.5f, -0.5f, 0.2f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Lithe::Renderer2D::DrawQuad({ -1.0f, 0.0f, 0.2f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });

		Lithe::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, 0.3f }, rotation, { 1.0f, 1.0f }, m_CheckerboardTexture, m_SquareColor, 1.0f);
		
		Lithe::Renderer2D::EndScene();

		Lithe::Renderer2D::BeginScene(m_CameraController.GetCamera());

		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				Lithe::Renderer2D::DrawQuad({ x, y, 0.1f }, { 0.45f, 0.45f }, color);
			}
		}
		Lithe::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	LI_PROFILE_FUNCTION();

	ImGui::Begin("Settings");

	auto stats = Lithe::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	{
		LI_PROFILE_SCOPE("ImGui Average FPS");

		static float fpsHistory[100] = {};
		static int fpsIndex = 0;
		static float fpsSum = 0.0f;

		float currentFps = 1.0f / ImGui::GetIO().DeltaTime;
		fpsSum -= fpsHistory[fpsIndex];
		fpsSum += currentFps;
		fpsHistory[fpsIndex] = currentFps;

		fpsIndex = (fpsIndex + 1) % 100;
		float avgFps = fpsSum / 100.0f;
		ImGui::Text("Avg FPS: %.1f", avgFps);
	}

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Lithe::Event& e)
{
	LI_PROFILE_FUNCTION();

	m_CameraController.OnEvent(e);
}
