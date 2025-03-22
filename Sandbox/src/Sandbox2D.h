#pragma once

#include <Lithe.h>

class Sandbox2D : public Lithe::Layer
{
public:
	Sandbox2D();
	Sandbox2D(Lithe::OrthographicCameraController& camera);
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Lithe::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Lithe::Event& e) override;
private:
	Lithe::OrthographicCameraController m_CameraController;
	Lithe::Ref<Lithe::Framebuffer> m_Framebuffer;

	Lithe::Ref<Lithe::Texture2D> m_CheckerboardTexture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};