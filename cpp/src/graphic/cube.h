#pragma once

#include "graphicUnit.h"
#include <vector>

class Cube : public GraphicUnit {
public:
    float size;

    Cube(Position pos, Color color, float size);
    Cube(Position pos, Color color);
    void createShape() override;
};