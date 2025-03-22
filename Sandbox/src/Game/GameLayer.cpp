#include "GameLayer.h"

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

GameLayer::GameLayer()
	: Layer("GameLayer"), m_CameraController(1280.0f / 720.0f, true)
{
}

GameLayer::GameLayer(Lithe::OrthographicCameraController& camera)
	: Layer("GameLayer"), m_CameraController(camera)
{
}

void GameLayer::OnAttach()
{
	LI_PROFILE_FUNCTION();

	m_SpriteSheet = Lithe::Texture2D::Create("assets/game/textures/RPGpack_sheet_2X.png");

	m_TextureStairs = Lithe::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 7, 6 }, { 128, 128 });
	m_TextureBarrel = Lithe::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 8, 2 }, { 128, 128 });
	m_TextureTree = Lithe::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 1 }, { 128, 128 }, { 1, 2 });

	m_MapWidth = s_MapWidth;
	m_MapHeight = static_cast<uint32_t>(strlen(s_MapTiles)) / s_MapWidth;

	s_TextureMap['D'] = Lithe::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 6, 11 }, { 128, 128 });
	s_TextureMap['W'] = Lithe::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 11, 11 }, { 128, 128 });

	m_CameraController.SetZoomLevel(5.0f);
}

void GameLayer::OnDetach()
{
	LI_PROFILE_FUNCTION();

}

void GameLayer::OnUpdate(Lithe::Timestep ts)
{
	LI_PROFILE_FUNCTION();

	{
		LI_PROFILE_SCOPE("GameLayer Renderer Prep");
		Lithe::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Lithe::RenderCommand::Clear();
	}

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

				Lithe::Renderer2D::DrawQuad({ x - m_MapWidth / 2.0f, m_MapHeight - y - m_MapHeight / 2.0f, 0.5f }, { 1.0f, 1.0f }, texture);
			}
		}

		/*Lithe::Renderer2D::DrawQuad({0.0f, 0.0f, 0.6f}, {20.0f, 20.0f}, m_SpriteSheet);
		Lithe::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.7f }, { 1.0f, 1.0f }, m_TextureStairs);
		Lithe::Renderer2D::DrawQuad({ 1.0f, 0.0f, 0.8f }, { 1.0f, 1.0f }, m_TextureBarrel);
		Lithe::Renderer2D::DrawQuad({ -1.0f, 0.0f, 0.8f }, { 1.0f, 2.0f }, m_TextureTree);*/

		Lithe::Renderer2D::EndScene();
	}
}

void GameLayer::OnEvent(Lithe::Event& e)
{
	LI_PROFILE_FUNCTION();

	m_CameraController.OnEvent(e);
}
