#include "graphicBuffer.h"
#include <glad/glad.h>
using namespace std;

GraphicBuffer::GraphicBuffer() {
    glGenVertexArrays(1, &(this->VAO));
    glGenBuffers(1, &(this->VBO));
    glGenBuffers(1, &(this->EBO));
}

void GraphicBuffer::setStride(GLuint location, GLuint size, GLsizei stride, void* offset) {
    glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(location);
    
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void GraphicBuffer::updateBuffers(vector<GLfloat>& vertices, vector<GLuint>& indices) {
    
    if(vertices.empty()) {
        cerr << "Buffer::bindAll error: Vertices is empty" << endl;
        return;
    }

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    if(!indices.empty()) {
        glBindVertexArray(this->VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    }
}

void GraphicBuffer::bindVAO() {
    glBindVertexArray(this->VAO);
}

void GraphicBuffer::unbindVAO() {
    glBindVertexArray(0);
}

void GraphicBuffer::unbindEBO() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GraphicBuffer::unbindVBO() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GraphicBuffer::unbindAll() {
    this->unbindVBO();
    this->unbindVAO();
    this->unbindEBO();
}

void GraphicBuffer::deleteBuffers() {
    glDeleteVertexArrays(1, &(this->VAO));
    glDeleteBuffers(1, &(this->VBO));
    glDeleteBuffers(1, &(this->EBO));  

}

