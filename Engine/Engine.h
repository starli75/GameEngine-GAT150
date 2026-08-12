#pragma once


#include "Random.h"
#include "Vector2.h"
#include "Vector3.h"
#include "MathUtils.h"
#include "Transform.h"
#include "File.h"
#include "StringUtils.h"

#include "Factory.h"


//systems
#include "Renderer.h"
#include "Input.h"
#include "GameTime.h"
#include "ParticleSystem.h"

#include "Actor.h"
#include "Scene.h"
#include "Game.h"
#include "Audio.h"
#include "Texture.h"
#include "Font.h"
#include "ResourceManager.h"
#include "Resource.h"
#include "Json.h"

namespace nu {
	class Engine
	{
	public:
		static Engine& Get() { static Engine engine; return engine; }

		bool Initialize();
		void Shutdown();

		void Update();

		Input& GetInput() { return m_input; }
		Renderer& GetRenderer() { return m_renderer; }
		Time& GetTime() { return m_time; }
		Audio& GetAudio() { return m_audio; }
		ParticleSystem& GetPS() { return m_particleSystem; }

	private:
		Engine() = default;
	private:
		Input m_input;
		Renderer m_renderer;
		Time m_time;
		Audio m_audio;
		ParticleSystem m_particleSystem;
	};
}
