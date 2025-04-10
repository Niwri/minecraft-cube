#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include "bufferClass.h"
#include "shaderClass.h"

//"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
using namespace std;

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "Yay", NULL, NULL);
    if(window == NULL) {
        cout << "main Error: Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0, 0, 800, 800);

    Shader* shader = new Shader("shaders/default.vert", "shaders/default.frag");
    Buffer* buffer = new Buffer();

    shader->link();

    GLfloat vertices[] = {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
         0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
         0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
         -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
         0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
         0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,
    };
    GLuint indices[] = {
        0, 3, 5,
        3, 2, 4,
        5, 4, 1
    };

    buffer->bindAll(vertices, indices, sizeof(vertices), sizeof(indices));
    buffer->setStride(3, 0);
    buffer->unbindAll();

    glfwSwapBuffers(window);

    cout << "Starting application!" << endl;
    // Main loop
    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        buffer->bindVAO();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    buffer->deleteBuffers();
    shader->unlink();

    delete buffer;
    delete shader;
    
    cout << "Ending application" << endl;
    glfwTerminate();
    return 0;
}