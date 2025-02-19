#pragma once
#include "rendering/renderer/lWindow.hpp"

namespace Ge
{
	enum ERendererType
	{
		OpenGL33,
		OpenGL45,
		Vulkan
	};

	struct SRendererCreateInfo
	{
		ERendererType e_renderer_type;
		SWindowInfo* p_window_info;
	};


	class Renderer
	{
	public:

		virtual ~Renderer() = default;
		virtual void Initialize(const SRendererCreateInfo& _rendererInfo) = 0;
		virtual void Release() = 0;

		Window* GetWindow();

	protected:

		bool m_initialized = false;
		Window* mp_window = nullptr;

	};

}