#include "graphicUnit.h"
    
GraphicUnit::GraphicUnit() {
    this->vertices.reserve(1000);
    this->indices.reserve(1000);
    this->indicesIndex = 0;
    this->verticesIndex = 0;
}

GraphicUnit::GraphicUnit(Position pos, Color color) : GraphicUnit() {
    this->pos = pos * SCALE;
    this->color = color;
}

GraphicUnit::~GraphicUnit() {
    this->vertices.erase(this->vertices.begin(), this->vertices.end());
    this->indices.erase(this->indices.begin(), this->indices.end());
}