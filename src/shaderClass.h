#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <string.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cerrno>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

std::string readShaderFile(string filename);

class Shader {
    public:
        GLuint vertexShader, fragmentShader, shaderProgram;
        string vertexShaderSource;
        string fragmentShaderSource;
        
        Shader(string vertexFile, string fragmentFile);

        void link();
        void unlink();
};

#endif