#include <iostream>
#include <stdexcept>
#include <cmath>


#include "GameEngine.hpp"
#include "../rendering/rasterization/RasterizationEngine.hpp"


namespace Ge
{

	GameEngine::~GameEngine()
	{
		Release();
	}

	void createTriangle(unsigned int& vao, unsigned int& vbo, unsigned int& ebo)
	{
		// Define the vertices and their associated colors for the triangle
		// Each vertex has a position (x, y, z) and a color (r, g, b)
		float triangleVertices[] = {
			0.0f, 1.0f, 0.0f,  // Position of vertex 1
			1.0f, 0.0f, 0.0f,  // Color of vertex 1 (Red)
			-1.f, -0.5f, 0.0f, // Position of vertex 2
			0.0f, 1.0f, 0.0f,  // Color of vertex 2 (Green)
			1.0f, -0.5f, 0.0f, // Position of vertex 3
			0.0f, 0.0f, 1.0f   // Color of vertex 3 (Blue)
		};

		// Define the indices that represent how to draw the triangle using the vertices
		unsigned int triangleIndices[] = {
			0, 1, 2 // The triangle consists of vertices 0, 1, and 2
		};

		// Generate a Vertex Array Object (VAO), Vertex Buffer Object (VBO),
		// and Element Buffer Object (EBO) to manage and store OpenGL state
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);

		// Bind the VAO to start recording the OpenGL state for this triangle
		glBindVertexArray(vao);

		// Bind the VBO to the GL_ARRAY_BUFFER target to store vertex data
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		// Upload the vertex data to the GPU
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

		// Bind the EBO to the GL_ELEMENT_ARRAY_BUFFER target to store index data
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		// Upload the index data to the GPU
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangleIndices), triangleIndices, GL_STATIC_DRAW);

		// Specify the layout of the vertex data:
		// Attribute 0: Position (x, y, z) - 3 floats, starting at offset 0
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0); // Enable attribute 0

		// Attribute 1: Color (r, g, b) - 3 floats, starting at offset 3 * sizeof(float)
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1); // Enable attribute 1

		// Unbind the VBO (optional, to prevent accidental modification of VBO data)
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Unbind the VAO (optional, to prevent accidental modification of VAO state)
		glBindVertexArray(0);
	}


	void GameEngine::Initialize(const SGameEngineCreateInfo& _GameEngineCreateInfo)
	{
		if (m_initialized)
			Release();

		switch (_GameEngineCreateInfo.p_rendering_engine_create_info->e_rendering_engine_type)
		{
		case Rasterization:
		{
			mp_rendering_engine = new RasterizationEngine();
			break;
		}
		case RaytracingCPU:
		{
			throw std::runtime_error("No RaytracingCPU implemented.");
		}
		case RaytracingGPU:
		{
			throw std::runtime_error("No RaytracingGPU implemented.");
		}
		}

		if (!mp_rendering_engine)
			throw std::bad_alloc();

		m_initialized = true;
		mp_rendering_engine->Initialize(*_GameEngineCreateInfo.p_rendering_engine_create_info);

		std::cout << "Game Engine initialized." << std::endl;

		// Simple triangle
		// Create triangle
		
		createTriangle(vao, vbo, ebo);

		// Initialize shader
		simpleShader.init(
			FileManager::read("../../../include/shaders/simple.vs"), // Vertex shader source
			FileManager::read("../../../include/shaders/simple.fs")  // Fragment shader source
		);

		// Get screen dimensions
		GLFWwindow* p_window = mp_rendering_engine->GetRenderer()->GetWindow()->GetHandle();
		int screenWidth, screenHeight;
		glfwGetFramebufferSize(p_window, &screenWidth, &screenHeight);

		// Camera setup
		glm::vec3 cameraPosition(0.f, 0.f, 2.f);       // Camera is placed at (0, 0, 2)
		glm::vec3 cameraViewDirection(0.f, 0.f, -1.f); // Camera looks towards the negative Z-axis

		// Model matrix
		model = 1.f; // Identity matrix, meaning no transformation on the model

		// View matrix
		view = glm::lookAt(
			cameraPosition,                       // Camera position
			cameraPosition + cameraViewDirection, // Target position (camera looks here)
			glm::vec3(0.f, 1.f, 0.f)              // Up vector (positive Y-axis)
		);

		// Projection matrix
		projection = glm::perspective(
			(float)M_PI_2,                            // Field of view (90 degrees in radians)
			(float)screenWidth / (float)screenHeight, // Aspect ratio (width / height)
			0.01f,                                    // Near clipping plane
			100.0f                                    // Far clipping plane
		);
	}

	void GameEngine::Release()
	{
		if (m_initialized)
		{
			if (mp_rendering_engine)
			{
				mp_rendering_engine->Release();

				delete mp_rendering_engine;
				mp_rendering_engine = nullptr;

				// Cleanup triangle
				glDeleteVertexArrays(1, &vao);
				glDeleteBuffers(1, &vbo);
				glDeleteBuffers(1, &ebo);
			}
		}
	}

	void GameEngine::Run()
	{
		if (!m_initialized)
			throw std::runtime_error("Game Engine not initialized");

		GLFWwindow* p_window = mp_rendering_engine->GetRenderer()->GetWindow()->GetHandle();

		// Timers
		double lag = 0.0;
		double previous = glfwGetTime();
		double SECONDS_PER_UPDATE = 1.0 / 60.0;

		// Main loop
		while (!glfwWindowShouldClose(p_window)) {

			

			float current = glfwGetTime();
			double elapsed = current - previous;
			previous = current;

			lag += elapsed;
			glfwPollEvents();

			float red = (std::sin(current * 0.5f) + 1.f) / 2.f;
			float green = (std::sin(current * 0.3f) + 1.f) / 2.f;
			float blue = (std::sin(current * 0.7f) + 1.f) / 2.f;

			while (lag >= SECONDS_PER_UPDATE)
			{
				// Game Logic
				lag -= SECONDS_PER_UPDATE;
			}

			// Clear the screen
			glClearColor(red, green, blue, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Render the triangle
			{
				// Activate the shader to use it for rendering
				simpleShader.use();

				// Update model matrix for rotating the triangle on Z-axis
				model = glm::rotate(
					glm::mat4(1.f),
					std::sin(current * 0.8f) / 4.f,
					glm::vec3(0.f, 0.f, -1.f));

				// Set shader uniforms
				simpleShader.setMat4("u_model", model);
				simpleShader.setMat4("u_view", view);
				simpleShader.setMat4("u_projection", projection);

				// Bind the VAO that stores the triangle's vertex data and settings
				glBindVertexArray(vao);

				// Issue the draw command
				glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

				// Unbind the VAO
				glBindVertexArray(0);
			}

			// Rendering
			mp_rendering_engine->Render(static_cast<float>(lag / SECONDS_PER_UPDATE));
		}
	}

}