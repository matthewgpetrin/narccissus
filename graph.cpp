#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "src/Mesh.hpp"
#include "src/Path.hpp"
#include "src/Dipole.hpp"

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
    using Scene = Scene<float>;

    Scene s01{(std::ifstream) "../magnolia.obj"};
    //Scene s01{{{{10.0, 10.0, 10.0}, {10, 10, 10}, {10, 10, 10}}}};

    for (int i = 0; i < s01.faces().size(); i++) {
        std::cout << "tri " << i << ": " << s01.faces()[i] << "\n";
    }

    //Trace<float> tx_rays{{{50, 50, 20},
    //{-1, -1, -.5}}};

    Dipole<float> dipole{{0, 0, 0}};

    std::vector<Ray<float>> tx_rays = dipole.transmit(256);

    std::vector<Trace<float>> tx_traces;

    for (const auto &ray: tx_rays) {
        tx_traces.push_back({ray, 5});
    }

    for (auto &tx_trace: tx_traces) {
        tx_trace.trace(s01);
    };

    std::vector<float> vs;

    float div = 100;

    for (const auto &face: s01.faces()) {
        for (int i = 0; i < 4; i++) {
            if (i == 3) {
                vs.push_back(face.nodes()[0].x / div);
                vs.push_back(face.nodes()[0].y / div);
                vs.push_back(face.nodes()[0].z / div);
            } else {
                vs.push_back(face.nodes()[i].x / div);
                vs.push_back(face.nodes()[i].y / div);
                vs.push_back(face.nodes()[i].z / div);
            }
        }
    }

    for (const auto &trace: tx_traces) {
        for (const auto &ray: trace.rays()) {
            for (int i = 0; i < 2; i++) {
                vs.push_back(ray.origin().x / div);
                vs.push_back(ray.origin().y / div);
                vs.push_back(ray.origin().z / div);
                vs.push_back(ray.direction().x * 10);
                vs.push_back(ray.direction().y * 10);
                vs.push_back(ray.direction().z * 10);
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
