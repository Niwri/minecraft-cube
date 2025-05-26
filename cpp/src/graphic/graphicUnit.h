#pragma once 

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "graphicSettings.h"

using namespace std;

struct Position {
    GLfloat x;
    GLfloat y;
    GLfloat z;

    Position operator*(float scale) {
        return {x * scale, y * scale, z * scale};
    }
};

struct Color {
    GLfloat r;
    GLfloat g;
    GLfloat b;
};

class GraphicUnit {

    public:
        vector<GLfloat> vertices;
        vector<GLuint> indices;
        int indicesIndex;
        int verticesIndex;

        Position pos;
        Color color;
    
        GraphicUnit();
        GraphicUnit(Position pos, Color color);
        ~GraphicUnit();

        virtual void createShape() = 0;
};