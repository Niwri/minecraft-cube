#include "triangle.h"
Triangle::Triangle(Position pos, Color color, float width, float height, float length) : GraphicUnit(pos, color) {
    this->width = width * SCALE;
    this->height = height * SCALE;
    this->length = length * SCALE;
    createShape();
}

void Triangle::createShape() {
    this->vertices = vector<GLfloat>({
        this->pos.x - width / 2, this->pos.y, this->pos.z, this->color.r, this->color.g, this->color.b,
        this->pos.x, this->pos.y + height, this->pos.z + length, this->color.r, this->color.g, this->color.b,
        this->pos.x + width / 2, this->pos.y, this->pos.z, this->color.r, this->color.g, this->color.b
    });

    this->indices = vector<GLuint>({ 0, 1, 2 });
}