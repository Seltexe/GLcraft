#include "rendering/renderer/OpenGL33/OpenGL33Renderer.hpp"

namespace Ge
{
	OpenGL33Renderer::~OpenGL33Renderer()
	{
		Release();
	}

	void OpenGL33Renderer::Initialize(const SRendererCreateInfo& _rendererInfo)
	{
		if (m_initialized)
			Release();

		m_initialized = true;
		m_window.Initialize(*_rendererInfo.p_window_info);
		mp_window = &m_window;

		std::cout << "OpenGL 3.3 renderer initialized." << std::endl;
	}

	void OpenGL33Renderer::Release()
	{
		if (m_initialized)
		{
			m_window.Release();
			mp_window = nullptr;
			m_initialized = false;
		}
	}
}