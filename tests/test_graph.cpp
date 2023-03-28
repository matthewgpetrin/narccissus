#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <vector>

#include "../src/Mesh.hpp"
#include "../src/Path.hpp"
#include "../src/Nrcc.hpp"

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

    float div = 1;
/*
    for (const auto &face: s01.faces) {
        for (int i = 0; i < 4; i++) {
            if (i == 3) {
                vs.push_back(face.points[0].x / div);
                vs.push_back(face.points[0].y / div );
                vs.push_back(face.points[0].z / div);
            } else {
                vs.push_back(face.points[i].x / div);
                vs.push_back(face.points[i].y / div );
                vs.push_back(face.points[i].z / div);
            }
        }
    }*/
    Mesh s02{{{{0, 0, 0}, {2, 0, 0}, {2, 2, 0}}}};

    int numrays = 500;
    std::vector<Vec3<float>> directs;
    for (int i = 0; i < numrays; i++) {
        directs.push_back(randomVector<float>().unit() * 3);
    }

    std::vector<Wave<float>> waves;
    for (int i = 0; i < numrays; i++) {
        //waves.push_back({{1, 1, 1}, directs[i], 1, 2.4e9, 0, nrcc::linear});
    }

    Nrcc<float> rt01(3);
    std::vector<Path<float>> paths;


    for (const auto &wave: waves) {
        //paths.push_back(rt01.trace(wave, s02));
    }

    std::cout << "POG";
    std::vector<Vec3<float>> starts;
    std::vector<Vec3<float>> ends;

    std::vector<float> ws;
    for (const auto &path: paths) {
        for (const auto &w: path.waves) {
            vs.push_back(w.origin.x / div);
            vs.push_back(w.origin.y / div);
            vs.push_back(w.origin.z / div);

            vs.push_back(w.direct.x / div * 100 + (w.origin.x / div));
            vs.push_back(w.direct.y / div * 100 + (w.origin.y / div));
            vs.push_back(w.direct.z / div * 100 + (w.origin.z / div));
            starts.push_back(w.origin);
            ends.push_back(w.direct);
        }
    }
    std::cout << "a =[";
    for (int i = 0; i < starts.size(); i++) {
        std::cout << starts[i] << "\n";
    }
    std::cout << "];\n\n";
    std::cout << "b =[";
    for (int i = 0; i < ends.size(); i++) {
        std::cout << ends[i] << "\n";
    }
    std::cout << "];\n\n";

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

    // Enable the vertex attribute array for the position and specify its layout
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

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
