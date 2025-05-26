#pragma once
#include <string.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cerrno>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

using namespace std;

class GraphicBuffer {
    public:
        GLuint VBO, EBO, VAO;
        
        GraphicBuffer();

        void setStride(GLuint location, GLuint size, GLsizei stride, void* offset);
        void updateBuffers(vector<GLfloat>& vertices, vector<GLuint>& indices);

        void bindVAO();
        
        void unbindVAO();
        void unbindVBO();
        void unbindEBO();
        void unbindAll();

        void deleteBuffers();
};