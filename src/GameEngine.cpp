#include <iostream>
#include <stdexcept>

#include "GameEngine.hpp"
#include "../rendering/rasterization/RasterizationEngine.hpp"

namespace Ge
{

	GameEngine::~GameEngine()
	{
		Release();
	}

	void GameEngine::Initialize(const SGameEngineCreateInfo& _GameEngineCreateInfo)
	{
		if (m_initialized)
			Release();

		switch (_GameEngineCreateInfo.p_rendering_engine_create_info->e_rendering_engine_type)
		{
		case Rasterization:
		{
			mp_rendering_engine = new RasterizationEngine();
			break;
		}
		case RaytracingCPU:
		{
			throw std::runtime_error("No RaytracingCPU implemented.");
		}
		case RaytracingGPU:
		{
			throw std::runtime_error("No RaytracingGPU implemented.");
		}
		}

		if (!mp_rendering_engine)
			throw std::bad_alloc();

		m_initialized = true;
		mp_rendering_engine->Initialize(*_GameEngineCreateInfo.p_rendering_engine_create_info);

		std::cout << "Game Engine initialized." << std::endl;
	}

	void GameEngine::Release()
	{
		if (m_initialized)
		{
			if (mp_rendering_engine)
			{
				mp_rendering_engine->Release();

				delete mp_rendering_engine;
				mp_rendering_engine = nullptr;
			}
		}
	}

	void GameEngine::Run()
	{
		if (!m_initialized)
			throw std::runtime_error("Game Engine not initialized");

		GLFWwindow* p_window = mp_rendering_engine->GetRenderer()->GetWindow()->GetHandle();

		// Timers
		double lag = 0.0;
		double previous = glfwGetTime();
		double SECONDS_PER_UPDATE = 1.0 / 60.0;

		// Main loop
		while (!glfwWindowShouldClose(p_window)) {

			// Clear the screen
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			double current = glfwGetTime();
			double elapsed = current - previous;
			previous = current;

			lag += elapsed;
			glfwPollEvents();

			while (lag >= SECONDS_PER_UPDATE)
			{
				// Game Logic
				lag -= SECONDS_PER_UPDATE;
			}

			// Rendering
			mp_rendering_engine->Render(static_cast<float>(lag / SECONDS_PER_UPDATE));
		}
	}

}