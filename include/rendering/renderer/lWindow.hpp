#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Ge
{
	struct SWindowInfo
	{
		int w_lenght;
		int w_height;
		const char* w_title;
	};


	class Window
	{
	private:

	protected:
		GLFWwindow* m_window = nullptr;
		bool m_initialized = false;

	public:

		virtual ~Window() = default;
		virtual void Initialize(const SWindowInfo& _windowInfo) = 0;
		virtual void Release() = 0;

		GLFWwindow* GetHandle();
	};

}