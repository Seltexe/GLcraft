#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Ge
{
	class IWindow
	{
	private:

	protected:
		GLFWwindow* m_window = nullptr;

	public:

		virtual ~IWindow() = default;
		virtual void Initialize() = 0;
		virtual void Release() = 0;

		GLFWwindow* GetHandle();
	};

}