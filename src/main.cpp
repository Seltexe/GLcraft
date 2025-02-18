#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../rendering/renderer/OpenGL33/OpenGL33Window.hpp"

int main() {
    Ge::OpenGL33Window window;
    Ge::SWindowInfo windowInfo{};

    windowInfo.w_lenght = 1280;
    windowInfo.w_height = 720;
    windowInfo.w_title = "GLCraft";

    try
    {
        window.Initialize(windowInfo);
    }
    catch (std::runtime_error& error)
    {
        std::cerr << "Error: " << error.what() << std::endl;
        return -1;
    }

    GLFWwindow* p_window = window.GetHandle();

    // Main loop
    while (!glfwWindowShouldClose(p_window)) {

        // Clear the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // Cube vertices
        float vertices[] = {
            // Front face
            -0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            // Back face
            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f
        };

        // Indices for the cube (using EBO)
        unsigned int indices[] = {
            // Front face
            0, 1, 2, 2, 3, 0,
            // Back face
            4, 5, 6, 6, 7, 4,
            // Left face
            4, 0, 3, 3, 7, 4,
            // Right face
            1, 5, 6, 6, 2, 1,
            // Top face
            3, 2, 6, 6, 7, 3,
            // Bottom face
            4, 5, 1, 1, 0, 4
        };

        // Set up VAO, VBO, and EBO
        unsigned int VAO, VBO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);


        // Swap buffers and poll events
        glfwSwapBuffers(p_window);
        glfwPollEvents();
    }

    // Clean up
    window.Release();

    return 0;
}