#pragma once
#include "RenderingEngine.hpp"



namespace Ge
{
	struct SGameEngineCreateInfo
	{
		SRenderingEngineCreateInfo* p_rendering_engine_create_info;
	};


	class GameEngine
	{
	public:

		~GameEngine();
		void Initialize(const SGameEngineCreateInfo& _GameEngineCreateInfo);
		void Release();
		void Run();


	private:

		bool m_initialized = false;
		RenderingEngine* mp_rendering_engine;
	};


}