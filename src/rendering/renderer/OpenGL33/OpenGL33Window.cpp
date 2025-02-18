#include "OpenGL33Window.hpp"

namespace Ge
{
	OpenGL33Window::~OpenGL33Window()
	{
		Release();
	}

	void OpenGL33Window::Initialize(const SWindowInfo& _windowInfo)
	{
        // Initialize GLFW
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return -1;
        }

        // Set OpenGL version to 3.3
        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


        // Create a window
        GLFWwindow* window = glfwCreateWindow(1280, 720, "GLcraft", nullptr, nullptr);
        if (!window) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);
        glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

        // Initialize Glad
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "Failed to initialize Glad" << std::endl;
            return -1;
        }

        // Set viewport and resize callback
        glViewport(0, 0, 1280, 720);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	}

	void OpenGL33Window::Release()
	{
	}
}

