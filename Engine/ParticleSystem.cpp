#include "pch.h"
#include "ParticleSystem.h"
#include "Renderer.h"
#include "Texture.h"
#include "ResourceManager.h"

namespace nu
{
	bool ParticleSystem::Initialize(size_t size)
	{
		// reserve # particles in container
		m_particles.resize(size);

		return true;
	}

	void ParticleSystem::Shutdown()
	{
		// clear all particles
		// TODO: clear() particles
		m_particles.clear();
	}

	void ParticleSystem::Update(float dt)
	{
		// update active particles
		for (auto& particle : m_particles)
		{
			if (/*TODO: particle is not active */!particle.active) continue;

			// reduce particle.lifespan by subtracting delta time
			// TODO: particle.lifespan -= delta time
			particle.lifespan -= dt;

			// set active if (particle.lifespan > 0);
			// TODO: particle.active = particle lifespan > 0
			particle.active = (particle.lifespan > 0);

			// update position with velocity (multiply by dt)
			// TODO: update position += with particle velocity * delta time
			particle.position += particle.velocity * dt;
		}
	}

	void ParticleSystem::Draw(Renderer& renderer, const std::string& filename)
	{
		// draw all active particlee
		for (auto& particle : m_particles)
		{
			if (particle.active)
			{
				// set particle color and draw point at current position
				// TODO: set color with particle color
				renderer.SetColorFloat(particle.color.r, particle.color.g, particle.color.b);
				// TODO: draw point with particle position
				renderer.DrawTexture(*Resources().Get<Texture>(filename, renderer), particle.position.x, particle.position.y);
			}
		}
	}

	void ParticleSystem::AddParticle(const Particle& particle)
	{
		// get free particle
		Particle* freeParticle = GetFreeParticle();
		// check if free particle is not nullptr
		if (freeParticle)
		{
			// set free particle object with particle
			// TODO: dereference (*) free particle and set it to particle
			*freeParticle = particle;
			// set particle active
			// TODO: set free particle active to true
			freeParticle->active = true;
		}
	}

	Particle* ParticleSystem::GetFreeParticle()
	{
		// find and return inactive particle 
		for (auto& particle : m_particles)
		{
			// return pointer to inactive particle
			if (/*TODO: particle is inactive*/!particle.active)
				return &particle;/*address (&) of particle*/
		}

		// no free particles, return nullptr
		return nullptr;
	}


}