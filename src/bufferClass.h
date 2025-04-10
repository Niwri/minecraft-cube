#ifndef BUFFER_CLASS_H
#define BUFFER_CLASS_H

#include <string.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cerrno>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Buffer {
    public:
        GLuint VBO, EBO, VAO;
        
        Buffer();

        void setStride(int stride, int offset);
        void bindAll(GLfloat* vertices, GLuint* indices, int vSize, int iSize);

        void bindVAO();
        
        void unbindVAO();
        void unbindVBO();
        void unbindEBO();
        void unbindAll();

        void deleteBuffers();
};

#endif