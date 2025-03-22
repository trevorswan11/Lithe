#pragma once

#include <Lithe.h>

class GameLayer : public Lithe::Layer
{
public:
	GameLayer();
	GameLayer(Lithe::OrthographicCameraController& camera);
	virtual ~GameLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Lithe::Timestep ts) override;
	void OnEvent(Lithe::Event& e) override;
private:
	Lithe::OrthographicCameraController m_CameraController;

	Lithe::Ref<Lithe::Texture2D> m_SpriteSheet;
	Lithe::Ref<Lithe::SubTexture2D> m_TextureStairs, m_TextureBarrel, m_TextureTree;

	uint32_t m_MapWidth, m_MapHeight;
	std::unordered_map<char, Lithe::Ref<Lithe::SubTexture2D>> s_TextureMap;
};

