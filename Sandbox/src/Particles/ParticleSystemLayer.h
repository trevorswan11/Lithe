#pragma once

#include <Lithe.h>

#include "Particles/ParticleSystem.h"

class ParticleSystemLayer : public Lithe::Layer
{
public:
	ParticleSystemLayer(uint32_t maxParticles = 999);
	ParticleSystemLayer(Lithe::OrthographicCameraController& camera, uint32_t maxParticles = 999);
	virtual ~ParticleSystemLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnEvent(Lithe::Event& event) override;
	virtual void OnUpdate(Lithe::Timestep ts) override;
	virtual void OnImGuiRender() override;
private:
	Lithe::OrthographicCameraController m_CameraController;
	ParticleProps m_Particle;
	ParticleSystem m_ParticleSystem;
};

