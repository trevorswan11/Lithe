#pragma once

#include <Lithe.h>

class Sandbox2D : public Lithe::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Lithe::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Lithe::Event& e) override;
private:
	Lithe::OrthographicCameraController m_CameraController;

	// TEMPORARY
	Lithe::Ref<Lithe::VertexArray> m_SquareVA;
	Lithe::Ref<Lithe::Shader> m_FlatColorShader;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};