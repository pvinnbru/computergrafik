#pragma once
// GLAD
#include <glad/gl.h>
// GLFW (include after glad)
#include <GLFW/glfw3.h>
// GLM
#ifdef _MSVC_VER
#pragma warning(push, 3)
#endif
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#ifdef _MSVC_VER
#pragma warning(pop)
#endif
// ImGUI
#include <imgui.h>

#include "Image.hpp"
#include "ObjectLoader.hpp"
#include "Resources.hpp"
#include "Shader.hpp"

class App {
public:
    App() { 

        // simple triangle
        triangleVertexBufferData = {
            -1.0f, -1.0f, 0.0f,
             1.0f, -1.0f, 0.0f,
             0.0f,  1.0f, 0.0f,
        };

        // haus vom nikolaus
        houseVertexBufferData = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
             0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
             0.5f, -0.5f, 0.0f
        };

        g_vertex_buffer_data = triangleVertexBufferData;

    }

    void updateVertexBuffer() {
        glGenBuffers(1, &vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, g_vertex_buffer_data.size() * sizeof(GLfloat), g_vertex_buffer_data.data(), GL_STATIC_DRAW);
    }

    void initializeVAO() {
        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
    }

    void init(GLFWwindow* window)
    {
        initializeVAO();
        updateVertexBuffer();
        programID = Shader::loadShaders(to_resource_path("vertex0.glsl"), to_resource_path("fragment0.glsl"));
        glUseProgram(programID);
    }

    void draw(GLFWwindow* window, float delta_time)
    {
        glClearColor(1.0f, 1.0f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glDrawArrays(drawingMode, 0, verticesCount);
        glDisableVertexAttribArray(0);
    }

    void on_key_change(GLFWwindow* window, int key, int scancode, int action, int mode)
    {
        (void)scancode;
        (void)mode;

        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }

        if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
            g_vertex_buffer_data = triangleVertexBufferData;
            drawingMode = GL_TRIANGLES;
            verticesCount = 3;
            updateVertexBuffer();
        }

        if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
            g_vertex_buffer_data = houseVertexBufferData;
            drawingMode = GL_LINE_STRIP;
            verticesCount = 9;
            updateVertexBuffer();
        }
    }

    void on_resize(GLFWwindow* window, int width, int height)
    {
        (void)window;
        glViewport(0, 0, width, height);
    }

private:

    std::vector<GLfloat> g_vertex_buffer_data;
    std::vector<GLfloat> triangleVertexBufferData;
    std::vector<GLfloat> houseVertexBufferData;

    GLuint vertexbuffer;
    GLuint programID;
    GLenum drawingMode = GL_TRIANGLES;
    int verticesCount = 3;
};
