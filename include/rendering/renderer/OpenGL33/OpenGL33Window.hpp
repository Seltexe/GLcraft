#pragma once
#include "../rendering/renderer/Window.hpp"
#include <exception>


namespace Ge
{
	class OpenGL33Window : public Window
	{
	private:

	public:
		~OpenGL33Window() override;
		void Initialize(const SWindowInfo& _windowInfo) final;
		void Release() final;
	};


}