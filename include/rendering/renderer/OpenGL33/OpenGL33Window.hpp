#pragma once
#include "../rendering/renderer/lWindow.hpp"
#include <stdexcept>


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