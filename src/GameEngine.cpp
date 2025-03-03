#include <iostream>
#include <stdexcept>
#include <cmath>


#include "GameEngine.hpp"
#include "../rendering/rasterization/RasterizationEngine.hpp"


namespace Ge
{
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
	float lastX = 800 / 2.0f;
	float lastY = 600 / 2.0f;
	bool firstMouse = true;

	void processInput(GLFWwindow* window, float deltaTime) {
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			camera.ProcessKeyboard(FORWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			camera.ProcessKeyboard(BACKWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			camera.ProcessKeyboard(LEFT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			camera.ProcessKeyboard(RIGHT, deltaTime);
	}

	void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
		if (firstMouse) {
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xOffset = xpos - lastX;
		float yOffset = lastY - ypos; // Reversed Y-axis

		lastX = xpos;
		lastY = ypos;

		camera.ProcessMouseMovement(xOffset, yOffset);
	}

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
			1.0f, 0.8f, 0.0f,  // Color of vertex 1 (Red)
			-1.f, -0.5f, 0.0f, // Position of vertex 2
			1.0f, 0.8f, 0.0f,  // Color of vertex 2 (Green)
			1.0f, -0.5f, 0.0f, // Position of vertex 3
			1.0f, 0.8f, 0.0f,   // Color of vertex 3 (Blue)
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

	void createSquare(unsigned int& vao, unsigned int& vbo, unsigned int& ebo)
	{
		// Define the vertices and their associated colors for the triangle
		// Each vertex has a position (x, y, z) and a color (r, g, b)
		float squareVertices[] = {
			// Positions          // Couleurs
			-1.0f,  1.0f, 0.0f,  1.0f, 0.8f, 0.0f, // Haut-gauche
			 1.0f,  1.0f, 0.0f,  1.0f, 0.8f, 0.0f, // Haut-droit
			-1.0f, -1.0f, 0.0f,  1.0f, 0.8f, 0.0f, // Bas-gauche
			 1.0f, -1.0f, 0.0f,  1.0f, 0.8f, 0.0f  // Bas-droit
		};

		// Define the indices that represent how to draw the square using the vertices
		unsigned int squareIndices[] = {
		0, 1, 2, // Premier triangle
		1, 3, 2  // Deuxi�me triangle
		};

		// Generate a Vertex Array Object (VAO), Vertex Buffer Object (VBO),
		// and Element Buffer Object (EBO) to manage and store OpenGL state
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);

		// Bind the VAO to start recording the OpenGL state for this square
		glBindVertexArray(vao);

		// Bind the VBO to the GL_ARRAY_BUFFER target to store vertex data
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		// Upload the vertex data to the GPU
		glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW);

		// Bind the EBO to the GL_ELEMENT_ARRAY_BUFFER target to store index data
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		// Upload the index data to the GPU
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(squareIndices), squareIndices, GL_STATIC_DRAW);

		// Specify the layout of the vertex data:
		// Attribute 0: Position (x, y, z) - 6 floats, starting at offset 0
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0); // Enable attribute 0

		// Attribute 1: Color (r, g, b) - 6 floats, starting at offset 6 * sizeof(float)
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1); // Enable attribute 1

		// Unbind the VBO (optional, to prevent accidental modification of VBO data)
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Unbind the VAO (optional, to prevent accidental modification of VAO state)
		glBindVertexArray(0);
	}

	void createCube(unsigned int& vao, unsigned int& vbo, unsigned int& ebo)
	{
		float cubeVertices[] = {
			// Positions          // Colors
			-1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, // 0 - Red
			 1.0f, -1.0f, -1.0f,  0.0f, 1.0f, 0.0f, // 1 - Green
			 1.0f,  1.0f, -1.0f,  0.0f, 0.0f, 1.0f, // 2 - Blue
			-1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 0.0f, // 3 - Yellow
			-1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 1.0f, // 4 - Magenta
			 1.0f, -1.0f,  1.0f,  0.0f, 1.0f, 1.0f, // 5 - Cyan
			 1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 1.0f, // 6 - White
			-1.0f,  1.0f,  1.0f,  0.0f, 0.0f, 0.0f  // 7 - Black
		};

		unsigned int cubeIndices[] = {
			0, 1, 2,  2, 3, 0,  // Back face
			1, 5, 6,  6, 2, 1,  // Right face
			5, 4, 7,  7, 6, 5,  // Front face
			4, 0, 3,  3, 7, 4,  // Left face
			3, 2, 6,  6, 7, 3,  // Top face
			4, 5, 1,  1, 0, 4   // Bottom face
		};

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);

		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

		// Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// Color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	unsigned int loadCubemap(std::vector<std::string> faces) {
		unsigned int textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
		//stbi_set_flip_vertically_on_load(false);

		int width, height, nrChannels;
		for (unsigned int i = 0; i < faces.size(); i++) {
			unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
			if (data) {
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				stbi_image_free(data);
			}
			else {
				std::cerr << "Failed to load cubemap texture at " << faces[i] << std::endl;
				stbi_image_free(data);
			}
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		return textureID;
	}

	void createSkybox(unsigned int& skyboxVAO, unsigned int& skyboxVBO, unsigned int& skyboxEBO) {
		float skyboxVertices[] = {
			// Positions
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f
		};

		unsigned int cubeIndices[] = {
			0, 1, 2,  2, 3, 0,  // Back face
			1, 5, 6,  6, 2, 1,  // Right face
			5, 4, 7,  7, 6, 5,  // Front face
			4, 0, 3,  3, 7, 4,  // Left face
			3, 2, 6,  6, 7, 3,  // Top face
			4, 5, 1,  1, 0, 4   // Bottom face
		};

		glGenVertexArrays(1, &skyboxVAO);
		glGenBuffers(1, &skyboxVBO);
		glGenBuffers(1, &skyboxEBO);

		glBindVertexArray(skyboxVAO);
		glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

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
		
		createCube(vao, vbo, ebo);

		// Initialize shader
		simpleShader.init(
			FileManager::read("shaders/simple.vs"), // Vertex shader source
			FileManager::read("shaders/simple.fs")  // Fragment shader source
		);

		skyboxShader.init(
			FileManager::read("shaders/skybox.vs"), // Vertex shader source
			FileManager::read("shaders/skybox.fs")  // Fragment shader source
		);

		// Get screen dimensions
		GLFWwindow* p_window = mp_rendering_engine->GetRenderer()->GetWindow()->GetHandle();
		int screenWidth, screenHeight;
		glfwGetFramebufferSize(p_window, &screenWidth, &screenHeight);

		// Camera setup
		glm::vec3 cameraPosition(0.f, 0.f, 5.f);       // Camera is placed at (0, 0, 2)
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


		// skybox

		std::vector<std::string> faces = {
			"skybox/px.png", // Right (+X)
			"skybox/nx.png", // Left (-X)
			"skybox/py.png", // Top (+Y)
			"skybox/ny.png", // Bottom (-Y)
			"skybox/pz.png", // Front (+Z)
			"skybox/nz.png"  // Back (-Z)
		};
		skyboxTexture = loadCubemap(faces);
		createSkybox(skyboxVAO, skyboxVBO, skyboxEBO);

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

		glfwSetCursorPosCallback(p_window, mouse_callback);
		glfwSetInputMode(p_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Hide cursor for FPS-like movement


		// Timers
		double lag = 0.0;
		double previous = glfwGetTime();
		double SECONDS_PER_UPDATE = 1.0 / 60.0;

		glEnable(GL_DEPTH_TEST);

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
				processInput(p_window, elapsed);
				view = camera.GetViewMatrix();
			}


			// Clear the screen
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Disable depth writing
			glDepthFunc(GL_LEQUAL);

			skyboxShader.use();
			skyboxShader.setInt("skybox", 0);
			skyboxShader.setMat4("u_view", glm::mat4(glm::mat3(view))); // Remove translation
			skyboxShader.setMat4("u_projection", projection);

			glBindVertexArray(skyboxVAO);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0);

			// Restore depth function
			glDepthFunc(GL_LESS);


			// Render the triangle
			{
				// Activate the shader to use it for rendering
				simpleShader.use();

				// Update model matrix for rotating the triangle on Z-axis
				/*model = glm::rotate(
					glm::mat4(1.f),
					current * 8.f,
					glm::vec3(0.f, 1.f, 0.f));


				model = glm::rotate(
					model,
					current * 3.f,
					glm::vec3(1.f, 0.f, 0.f));*/

				// Set shader uniforms
				simpleShader.setMat4("u_model", model);
				simpleShader.setMat4("u_view", view);
				simpleShader.setMat4("u_projection", projection);

				// Bind the VAO that stores the triangle's vertex data and settings
				glBindVertexArray(vao);

				// Issue the draw command
				glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0); // Change this if you want to draw multiple verticies

				// Unbind the VAO
				glBindVertexArray(0);
			}

			// Rendering
			mp_rendering_engine->Render(static_cast<float>(lag / SECONDS_PER_UPDATE));
		}
	}

}