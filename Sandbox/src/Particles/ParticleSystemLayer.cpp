#include "ParticleSystemLayer.h"

#include <imgui/imgui.h>

#include <glm/gtc/type_ptr.hpp>

ParticleSystemLayer::ParticleSystemLayer(uint32_t maxParticles)
	: Layer("ParticleSystemLayer"), m_CameraController(1280.0f / 720.0f, true), m_ParticleSystem(maxParticles)
{
}

ParticleSystemLayer::ParticleSystemLayer(Lithe::OrthographicCameraController& camera, uint32_t maxParticles)
	: Layer("ParticleSystemLayer"), m_CameraController(camera), m_ParticleSystem(maxParticles)
{
}

ParticleSystemLayer::~ParticleSystemLayer()
{
}

void ParticleSystemLayer::OnAttach()
{
	LI_PROFILE_FUNCTION();

	m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 1.0f;
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 3.0f, 1.0f };
	m_Particle.Position = { 0.0f, 0.0f };
}

void ParticleSystemLayer::OnDetach()
{
	LI_PROFILE_FUNCTION();
}

void ParticleSystemLayer::OnEvent(Lithe::Event& event)
{
	LI_PROFILE_FUNCTION();

	m_CameraController.OnEvent(event);
}

void ParticleSystemLayer::OnUpdate(Lithe::Timestep ts)
{
	LI_PROFILE_FUNCTION();

	m_CameraController.OnUpdate(ts);

	if (Lithe::Input::IsMouseButtonPressed(LI_MOUSE_BUTTON_LEFT))
	{
		auto [x, y] = Lithe::Input::GetMousePos();
		auto width = Lithe::Application::Get().GetWindow().GetWidth();
		auto height = Lithe::Application::Get().GetWindow().GetHeight();

		auto& bounds = m_CameraController.GetBounds();
		auto& pos = m_CameraController.GetCamera().GetPosition();
		x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
		y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
		m_Particle.Position = { x + pos.x, y + pos.y };
		for (int i = 0; i < 5; i++)
			m_ParticleSystem.Emit(m_Particle);
	}

	m_ParticleSystem.OnUpdate(ts);
	m_ParticleSystem.OnRender(m_CameraController.GetCamera());
}

void ParticleSystemLayer::OnImGuiRender()
{
	LI_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Birth Color", glm::value_ptr(m_Particle.ColorBegin));
	ImGui::ColorEdit4("Death Color", glm::value_ptr(m_Particle.ColorEnd));
	ImGui::DragFloat("Life Time", &m_Particle.LifeTime, 0.1f, 0.0f, 1000.0f);
	ImGui::End();
}
