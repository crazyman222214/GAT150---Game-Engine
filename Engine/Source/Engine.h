#pragma once
#include "Renderer.h"
#include "Input.h"
#include "Audio.h"
#include "ETime.h"
#include "Vector2.h"
#include "Random.h"
#include "MathUtils.h"
#include "Particle.h"
#include "Model.h"
#include "Transform.h"

#include <SDL.h>
#include <fmod.hpp>
#include "ParticleSystem.h"

class Engine
{
public:
	Engine() = default;
	~Engine() = default;

	bool Initialize();
	void Shutdown();

	void Update();

	Renderer& GetRenderer() { return *m_renderer; }
	Input& GetInput() { return *m_input; }
	Audio& GetAudio() { return *m_audio; }
	Time& GetTime() { return *m_time; }
	ParticleSystem& GetPS() { return *m_ps; }

	bool IsQuit() { return quit; }

private:
	bool quit = false;

	std::unique_ptr<ParticleSystem> m_ps;
	std::unique_ptr<Time> m_time;
	std::unique_ptr<Renderer> m_renderer;
	std::unique_ptr<Input> m_input;
	std::unique_ptr<Audio> m_audio;

};


extern Engine g_engine;	