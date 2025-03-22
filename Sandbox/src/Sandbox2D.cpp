#include "Sandbox2D.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static const uint32_t s_MapWidth = 24;
static const char* s_MapTiles = 
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWWDDDDDDDDDDWWWWWWW"
"WWWWWDDDDDDDDDDDDDDWWWWW"
"WWWWDDDDDDDDDDDDDDDDWWWW"
"WWWDDDDDDDDDDDDDDDDDDWWW"
"WWDDDDDDDDDDDDDDDDDDDDWW"
"WDDDDDDWWWDDDDDDDDDDDDDW"
"WWDDDDDWWWDDDDDDDDDDDDWW"
"WWWDDDDDDDDDDDDDDDDDDWWW"
"WWWWDDDDDDDDDDDDDDDDWWWW"
"WWWWWDDDDDDDDDDDDDDWWWWW"
"WWWWWWWDDDDDDDDDDWWWWWWW"
"WWWWWWWWDDDDDDDDWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW";

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
	m_SpriteSheet = Lithe::Texture2D::Create("assets/game/textures/RPGpack_sheet_2X.png");

	m_TextureStairs = Lithe::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 7, 6 }, { 128, 128 });
	m_TextureBarrel = Lithe::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 8, 2 }, { 128, 128 });
	m_TextureTree = Lithe::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 1 }, { 128, 128 }, { 1, 2 });

	m_MapWidth = s_MapWidth;
	m_MapHeight = static_cast<uint32_t>(strlen(s_MapTiles)) / s_MapWidth;

	s_TextureMap['D'] = Lithe::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 6, 11 }, { 128, 128 });
	s_TextureMap['W'] = Lithe::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 11, 11 }, {128, 128});

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

#if 0
	{
		LI_PROFILE_SCOPE("Sandbox2D Renderer Draw");

		static float rotation = 0.0f;
		rotation += ts * 1.0f;

		Lithe::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Lithe::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f);
		
		Lithe::Renderer2D::DrawRotatedQuad({ -1.0f, -3.0f, 0.2f }, glm::radians(20.0f), { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Lithe::Renderer2D::DrawQuad({ 0.5f, -0.5f, 0.2f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Lithe::Renderer2D::DrawQuad({ -1.0f, 0.0f, 0.2f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });

		Lithe::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, 0.3f }, rotation, { 1.0f, 1.0f }, m_CheckerboardTexture, { 0.2f, 0.8f, 0.3f, 1.0f }, 1.0f);
		
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
#endif

	{
		LI_PROFILE_SCOPE("SpriteSheet Draw");
		Lithe::Renderer2D::BeginScene(m_CameraController.GetCamera());

		for (uint32_t y = 0; y < m_MapHeight; y++)
		{
			for (uint32_t x = 0; x < m_MapWidth; x++)
			{
				char tileType = s_MapTiles[x + y * m_MapWidth];
				Lithe::Ref<Lithe::SubTexture2D> texture;
				
				if (auto found = s_TextureMap.find(tileType); found != s_TextureMap.end())
					texture = found->second;
				else texture = m_TextureBarrel;

				Lithe::Renderer2D::DrawQuad({ x - m_MapWidth / 2.0f, m_MapHeight - y - m_MapHeight / 2.0f, 0.5f }, {1.0f, 1.0f}, texture);
			}
		}

		/*Lithe::Renderer2D::DrawQuad({0.0f, 0.0f, 0.6f}, {20.0f, 20.0f}, m_SpriteSheet);
		Lithe::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.7f }, { 1.0f, 1.0f }, m_TextureStairs);
		Lithe::Renderer2D::DrawQuad({ 1.0f, 0.0f, 0.8f }, { 1.0f, 1.0f }, m_TextureBarrel);
		Lithe::Renderer2D::DrawQuad({ -1.0f, 0.0f, 0.8f }, { 1.0f, 2.0f }, m_TextureTree);*/

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
	m_CameraController.OnEvent(e);
}
