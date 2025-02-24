#pragma once
#include "RenderingEngine.hpp"
#include "Shader.hpp"
#include "fileManager.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifndef M_PI_2
#define M_PI_2 1.57079632679489661923
#endif



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

		Shader simpleShader;
		bool m_initialized = false;
		RenderingEngine* mp_rendering_engine;

		unsigned int vao, vbo, ebo;
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
	};


}