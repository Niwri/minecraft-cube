#pragma once

#include "graphicUnit.h"
#include <vector>

class Triangle : public GraphicUnit {
public:
    float width, length, height;
    Triangle(Position pos, Color color, float width, float height, float length);
    void createShape() override;
};