#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <vector>

#include "../include/Mesh.hpp"
#include "../include/Path.hpp"

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Set GLFW window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window
    GLFWwindow *window = glfwCreateWindow(1200, 900, "OpenGL", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    // Make the context of the specified window current for the calling thread
    glfwMakeContextCurrent(window);

    // Load OpenGL function pointers with GLAD
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        glfwTerminate();
        return -1;
    }

    // TESTING OBJ READING
    using Mesh = Mesh<float>;

    Mesh s01{(std::ifstream) "../maps/stevens.obj"};

    std::vector<float> vs;

    float div = 500;

    for (const auto &face: s01.faces) {
        for (int i = 0; i < 4; i++) {
            if (i == 3) {
                vs.push_back(face.points[0].x / div);
                vs.push_back(face.points[0].z / div );
                vs.push_back(face.points[0].y / div);
            } else {
                vs.push_back(face.points[i].x / div);
                vs.push_back(face.points[i].z / div );
                vs.push_back(face.points[i].y / div);
            }
        }
    }

    // Define the vertices of the line
    std::vector<float> vertices = vs;

    // Generate and bind a vertex array object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Generate a vertex buffer object and copy the vertex data to it
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    // Enable the vertex attribute array for the position and specify its layout
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);

    // Unbind the VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // Bind the VAO
        glBindVertexArray(vao);


        // Draw the lines
        glDrawArrays(GL_LINES, 0, vertices.size() / 3);

        // Unbind the VAO
        glBindVertexArray(0);

        // Swap the front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Clean up resources
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glfwTerminate();
    return 0;
}
