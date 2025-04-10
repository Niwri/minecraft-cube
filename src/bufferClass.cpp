#include "bufferClass.h"
#include <glad/glad.h>
using namespace std;

Buffer::Buffer() {
    glGenVertexArrays(1, &(this->VAO));
    glGenBuffers(1, &(this->VBO));
    glGenBuffers(1, &(this->EBO));
}

void Buffer::setStride(int stride, int offset) {
    glVertexAttribPointer(offset, stride, GL_FLOAT, GL_FALSE, stride * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(0);
}

void Buffer::bindAll(GLfloat* vertices, GLuint* indices, int vSize, int iSize) {
    
    if(vertices == nullptr) {
        cerr << "Buffer::bindAll error: Vertices input is null" << endl;
    }

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    cout << sizeof(vertices);
    glBufferData(GL_ARRAY_BUFFER, vSize, vertices, GL_STATIC_DRAW);

    if(indices != nullptr) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, iSize, indices, GL_STATIC_DRAW);
    }
}

void Buffer::bindVAO() {
    glBindVertexArray(this->VAO);
}

void Buffer::unbindVAO() {
    glBindVertexArray(0);
}

void Buffer::unbindEBO() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Buffer::unbindVBO() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Buffer::unbindAll() {
    this->unbindVBO();
    this->unbindVAO();
    this->unbindEBO();
}

void Buffer::deleteBuffers() {
    glDeleteVertexArrays(1, &(this->VAO));
    glDeleteBuffers(1, &(this->VBO));
    glDeleteBuffers(1, &(this->EBO));  

}

