#include "ParticleSystem.h"

#include <imgui/imgui.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glm/gtc/constants.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

std::mt19937 Random::s_RandomEngine;
std::uniform_int_distribution<std::mt19937::result_type> Random::s_Distribution;

ParticleSystem::ParticleSystem(uint32_t maxParticles)
	: m_PoolIndex(maxParticles - 1)
{
	m_ParticlePool.resize(maxParticles);
}

void ParticleSystem::OnUpdate(Lithe::Timestep ts)
{
	LI_PROFILE_FUNCTION();

	for (auto& particle : m_ParticlePool)
	{
		if (!particle.Active)
		{
			particle.LifeRemaining = 0.0f;
			continue;
		}

		if (particle.LifeRemaining <= 0.0f)
		{
			particle.LifeRemaining = 0.0f;
			particle.Active = false;
			continue;
		}

		particle.LifeRemaining -= ts;
		particle.Position += particle.Velocity * (float)ts;
		particle.Rotation += 0.01f * ts;
	}
}

void ParticleSystem::OnRender(Lithe::OrthographicCamera& camera)
{
	LI_PROFILE_FUNCTION();

	Lithe::Renderer2D::BeginScene(camera);
	for (auto& particle : m_ParticlePool)
	{
		if (!particle.Active)
			continue;

		// Fade away particles
		float life = particle.LifeRemaining / particle.LifeTime;
		glm::vec4 color = glm::lerp(particle.ColorEnd, particle.ColorBegin, life);
		//color.a = color.a * life;
		
		float size = glm::lerp(particle.SizeEnd, particle.SizeBegin, life);

		Lithe::Renderer2D::DrawRotatedQuad({ particle.Position.x, particle.Position.y, 0.4f }, particle.Rotation, { size, size }, color);
	}
	Lithe::Renderer2D::EndScene();
}

void ParticleSystem::Emit(const ParticleProps& particleProps)
{
	LI_PROFILE_FUNCTION();

	Particle& particle = m_ParticlePool[m_PoolIndex];
	particle.Active = true;
	particle.Position = particleProps.Position;
	particle.Rotation = Random::Float() * 2.0f * glm::pi<float>();

	// Velocity
	particle.Velocity = particleProps.Velocity;
	particle.Velocity.x += particleProps.VelocityVariation.x * (Random::Float() - 0.5f);
	particle.Velocity.y += particleProps.VelocityVariation.y * (Random::Float() - 0.5f);

	// Color
	particle.ColorBegin = particleProps.ColorBegin;
	particle.ColorEnd = particleProps.ColorEnd;

	particle.LifeTime = particleProps.LifeTime;
	particle.LifeRemaining = particleProps.LifeTime;
	particle.SizeBegin = particleProps.SizeBegin + particleProps.SizeVariation * (Random::Float() - 0.5f);
	particle.SizeEnd = particleProps.SizeEnd;

	m_PoolIndex = --m_PoolIndex % m_ParticlePool.size();
}
