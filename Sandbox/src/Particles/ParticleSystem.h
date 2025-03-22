#pragma once

#include <Lithe.h>

#include <random>

class Random
{
public:
	static void Init()
	{
		s_RandomEngine.seed(std::random_device()());
	}

	static float Float()
	{
		return (float)s_Distribution(s_RandomEngine) / (float)std::numeric_limits<uint32_t>::max();
	}

private:
	static std::mt19937 s_RandomEngine;
	static std::uniform_int_distribution<std::mt19937::result_type> s_Distribution;
};

struct ParticleProps
{
	glm::vec2 Position;
	glm::vec2 Velocity, VelocityVariation;
	glm::vec4 ColorBegin, ColorEnd;
	float SizeBegin, SizeEnd, SizeVariation;
	float LifeTime = 5.0f;
};

class ParticleSystem
{
public:
	ParticleSystem(uint32_t maxParticles = 1000);

	void OnUpdate(Lithe::Timestep ts);
	void OnRender(Lithe::OrthographicCamera& camera);

	void Emit(const ParticleProps& particleProps);
private:
	struct Particle
	{
		glm::vec2 Position;
		glm::vec2 Velocity;
		glm::vec4 ColorBegin, ColorEnd;
		float Rotation = 0.0f;
		float SizeBegin, SizeEnd;

		float LifeTime = 5.0f;
		float LifeRemaining = 0.0f;

		bool Active = false;
	};
private:
	std::vector<Particle> m_ParticlePool;
	uint32_t m_PoolIndex;
};