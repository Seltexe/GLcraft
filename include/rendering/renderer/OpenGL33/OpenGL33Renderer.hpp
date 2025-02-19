#pragma once
#include <iostream>
#include "rendering/renderer/Renderer.hpp"
#include "rendering/renderer/OpenGL33/OpenGL33Window.hpp"

namespace Ge
{

	class OpenGL33Renderer : public Renderer
	{
	public:

		~OpenGL33Renderer() override;
		void Initialize(const SRendererCreateInfo& _rendererInfo) final;
		void Release() final;

	private:
		OpenGL33Window m_window;

	};

}