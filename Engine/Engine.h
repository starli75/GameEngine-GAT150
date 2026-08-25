#pragma once


#include "Core/Random.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/MathUtils.h"
#include "Math/Transform.h"
#include "Core/File.h"
#include "Json.h"
#include "Core/StringUtils.h"

#include "Core/Factory.h"


//systems
#include "Audio/Audio.h"
#include "Renderer/Renderer.h"
#include "Input.h"
#include "Core/GameTime.h"
#include "Renderer/ParticleSystem.h"

#include "Framework/Actor.h"
#include "Framework/Scene.h"
#include "Framework/Game.h"
#include "Renderer/Texture.h"
#include "Renderer/Font.h"
#include "Resources/ResourceManager.h"
#include "Resources/Resource.h"
#include "Physics/Physics.h"


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

		Physics& GetPhysics() { return m_physics; }

	private:
		Engine() = default;
	private:
		Input m_input;
		Renderer m_renderer;
		Time m_time;
		Audio m_audio;
		ParticleSystem m_particleSystem;
		Physics m_physics;
	};
}
