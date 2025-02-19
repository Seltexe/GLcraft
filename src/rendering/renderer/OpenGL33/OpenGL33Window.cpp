#include "OpenGL33Window.hpp"
#include "errorReporting.h"

namespace Ge
{
    void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }

	OpenGL33Window::~OpenGL33Window()
	{
		Release();
	}

	void OpenGL33Window::Initialize(const SWindowInfo& _windowInfo)
	{
        if (m_initialized)
            Release();


        // Initialize GLFW
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW!");
        }

        //glfwSetErrorCallback(glDebugOutput);
        // Set OpenGL version to 3.3
        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


        // Create a window
        GLFWwindow* window = glfwCreateWindow(_windowInfo.w_lenght, _windowInfo.w_height, _windowInfo.w_title, nullptr, nullptr);
        if (!window) {
            glfwTerminate();
            throw std::runtime_error("Failed to initialize GLFWwindow!");
        }
        glfwMakeContextCurrent(window);
        glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

        // Initialize Glad
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            glfwTerminate();
            throw std::runtime_error("Failed to initialize Glad!");
        }

        // Set viewport and resize callback
        glViewport(0, 0, 1280, 720);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        this->m_window = window;
	}

	void OpenGL33Window::Release()
	{
        if (m_initialized)
        {
            glfwTerminate();
            m_window = nullptr;

            m_initialized = false;
        }
	}
}

