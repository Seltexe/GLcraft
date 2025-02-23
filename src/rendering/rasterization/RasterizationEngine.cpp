#include <iostream>

#include "../rendering/rasterization/RasterizationEngine.hpp"
#include "OpenGL33Renderer.hpp"

namespace Ge
{

	RasterizationEngine::~RasterizationEngine()
	{
		Release();
	}

	void RasterizationEngine::Initialize(const SRenderingEngineCreateInfo& _renderingEngineCreateInfo)
	{
		if (m_initialized)
			Release();


		switch (_renderingEngineCreateInfo.p_renderer_create_info->e_renderer_type)
		{
			case OpenGL33: 
			{ 
				mp_renderer = new OpenGL33Renderer(); 
				break; 
			}
			case OpenGL45:
			{
				throw std::runtime_error("OpenGL 4.5 renderer not implemented.");
			}
			case Vulkan:
			{
				throw std::runtime_error("Vulkan renderer not implemented.");
			}
		}

		if (!mp_renderer)
			throw std::bad_alloc();

		m_initialized = true;
		mp_renderer->Initialize(*_renderingEngineCreateInfo.p_renderer_create_info);

		std::cout << "Rasterization engine initialized" << std::endl;
	}

	void RasterizationEngine::Release()
	{
		if (m_initialized)
		{
			if (mp_renderer)
			{
				mp_renderer->Release();
				delete mp_renderer;

				mp_renderer = nullptr;
			}

			m_initialized = false;
			std::cout << "Rasterization engine killed" << std::endl;
		}
	}

	void RasterizationEngine::Render(float _lag)
	{
		glfwSwapBuffers(mp_renderer->GetWindow()->GetHandle());
	}

}

