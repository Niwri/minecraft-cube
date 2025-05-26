#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <chrono>
#include "graphic/graphic.h"
#include "graphic/graphicSettings.h"
#include "input/input.h"

//"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
using namespace std;



int main() {

    // Setting up GLFW and Windows
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "Minecraft AR", NULL, NULL);
    if(window == NULL) {
        cout << "main Error: Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0, 0, WIDTH, HEIGHT);
    glEnable(GL_DEPTH_TEST);

    // Setting up shaders layout
    Shader* shader = new Shader("shaders/default.vert", "shaders/default.frag");
    GraphicBuffer* buffer = new GraphicBuffer();

    shader->link();
    shader->use();

    GraphicManager graphicManager;
    // Triangle* triA = new Triangle({-0.5f / 2, -0.5f * float(sqrt(3)) / 3, 0.0f}, {1.0f, 0.0f, 0.2f}, 0.5f, 1.5f * float(sqrt(3)) / 6, 0.0f);
    // Triangle* triB = new Triangle({0.0f, 0.5f * float(sqrt(3)) / 6, 0.0f}, {0.0f, 1.0f, 0.2f}, 0.5f, 1.5f * float(sqrt(3)) / 6, 0.0f);
    // Triangle* triC = new Triangle({0.5f / 2, -0.5f * float(sqrt(3)) / 3, 0.0f}, {1.0f, 1.0f, 0.2f}, 0.5f, 1.5f * float(sqrt(3)) / 6, 0.0f);
    // graphicManager.addUnit(triA);
    // graphicManager.addUnit(triB);
    // graphicManager.addUnit(triC);
    Cube* cubeA = new Cube({0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.2f}, 1.0f);
    Cube* cubeB = new Cube({1.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.2f}, 1.0f);
    graphicManager.addUnit(cubeA);
    graphicManager.addUnit(cubeB);

    // Setting up openGL buffers
    buffer->updateBuffers(graphicManager.vertices, graphicManager.indices);
       
    buffer->setStride(0, 3, STRIDE * sizeof(GLfloat), (void*)(0)); // For vertices
    buffer->setStride(1, 3, STRIDE * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat))); // For colors

    // Set up Camera (velocity, sensitivity, position, orientation)
    Camera* camera = new Camera();
    camera->setAspectRatio((float)WIDTH/(float)HEIGHT);
    camera->setPosition(glm::vec3(0.0f, 0.0f, 2.0f));
    camera->setShaderID(shader->shaderProgram);
    camera->setFOV(45.0f, 0.001f, 100.0f);
    camera->setVelocity(1.0f);
    camera->setSensitivity(0.05f);
    camera->updateRender();

    // Set up inputs
    KeyboardInputController keyboard;
	MouseInputController mouseController;	



    float deltaFPS = 1/FPS;
    glfwSwapBuffers(window);

    cout << "Starting application!" << endl;
    auto timeNow = chrono::high_resolution_clock::now();
    while(!glfwWindowShouldClose(window)) {

        double deltaTime = chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - timeNow).count();
        if (deltaTime <= deltaFPS) continue;
        timeNow = chrono::high_resolution_clock::now();
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader->use();
        if (glfwGetWindowAttrib(window, GLFW_FOCUSED) != 0) {
            mouseController.cameraControl(camera, window, WIDTH, HEIGHT); 
            keyboard.cameraControl(camera, deltaTime); 
            camera->updateRender();
        }
        
        buffer->bindVAO();
        glDrawElements(GL_TRIANGLES, graphicManager.indices.size(), GL_UNSIGNED_INT, (void*)(0 * sizeof(GLuint)));
        buffer->unbindVAO();
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    keyboard.unHook();
    buffer->deleteBuffers();
    shader->unlink();

    delete buffer;
    delete shader;
    
    cout << "Ending application" << endl;
    glfwTerminate();
    return 0;
}