#include "cube.h"

Cube::Cube(Position pos, Color color, float size) : GraphicUnit(pos, color) {
    this->size = size * SCALE;
    createShape();
}

Cube::Cube(Position pos, Color color) : Cube(pos, color, 1.0f) {
}


void Cube::createShape() {
    float halfSize = this->size / 2.0f;
    
    this->vertices = vector<GLfloat>({
        // Front face
        this->pos.x - halfSize, this->pos.y - halfSize, this->pos.z + halfSize, this->color.r, this->color.g, this->color.b, // Bottom left 
        this->pos.x - halfSize, this->pos.y + halfSize, this->pos.z + halfSize, this->color.r, this->color.g, this->color.b, // Top left
        this->pos.x + halfSize, this->pos.y - halfSize, this->pos.z + halfSize, this->color.r, this->color.g, this->color.b, // Bottom right
        this->pos.x + halfSize, this->pos.y + halfSize, this->pos.z + halfSize, this->color.r, this->color.g, this->color.b, // Top right

        // Back face
        this->pos.x - halfSize, this->pos.y - halfSize, this->pos.z - halfSize, this->color.r, this->color.g, this->color.b, // Bottom left
        this->pos.x - halfSize, this->pos.y + halfSize, this->pos.z - halfSize, this->color.r, this->color.g, this->color.b, // Top left
        this->pos.x + halfSize, this->pos.y - halfSize, this->pos.z - halfSize, this->color.r, this->color.g, this->color.b, // Bottom right
        this->pos.x + halfSize, this->pos.y + halfSize, this->pos.z - halfSize, this->color.r, this->color.g, this->color.b // Top right
    });
    
    // Define the 12 triangles (6 faces, 2 triangles per face)
    this->indices = vector<GLuint>({
        // // Front Face
        0, 1, 2,
        1, 2, 3,

        // Back Face
        4, 5, 6,
        5, 6, 7,

        // Top Face
        1, 3, 5,
        3, 5, 7,

        // Bottom Face
        0, 2, 4,
        2, 4, 6,

        // Left Face
        0, 1, 4,
        1, 4, 5,

        // Right Face
        2, 3, 6,
        3, 6, 7
    });
}