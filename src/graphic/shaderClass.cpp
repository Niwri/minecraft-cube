#include "shaderClass.h"

string readShaderFile(string filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "readShaderFile Error: Could not open file " << filePath << std::endl;
        return "";
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return content;
}

Shader::Shader(string vertexFile, string fragmentFile) {
    this->vertexShaderSource = readShaderFile(vertexFile);
    this->fragmentShaderSource = readShaderFile(fragmentFile);  
}

void Shader::link() {
    if(this->vertexShaderSource.length() == 0) {
        std::cerr << "attachShaders Error: VertexShaderSource not initialized" << std::endl;
        return;
    }

    if(this->fragmentShaderSource.length() == 0) {
        std::cerr << "attachShaders Error: FragmentShaderSource not initialized" << std::endl;
        return;
    }

    this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* vertexSource = this->vertexShaderSource.c_str();
    glShaderSource(this->vertexShader, 1, &vertexSource, NULL);
    glCompileShader(this->vertexShader);

    // Check vertex shader compilation
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
    }
    
    this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar* fragmentSource = this->fragmentShaderSource.c_str();
    glShaderSource(this->fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(this->fragmentShader);

    // Check fragment shader compilation
    glGetShaderiv(this->fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(this->fragmentShader, 512, NULL, infoLog);
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
    }

    this->shaderProgram = glCreateProgram();
    glAttachShader(this->shaderProgram, this->vertexShader);
    glAttachShader(this->shaderProgram, this->fragmentShader);
    glLinkProgram(this->shaderProgram);

    // Check shader program linking
    glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->shaderProgram, 512, NULL, infoLog);
        cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
    }

    glDeleteShader(this->vertexShader);
    glDeleteShader(this->fragmentShader);
}

void Shader::use() {
    glUseProgram(this->shaderProgram);
}

void Shader::unlink() {
    glDeleteProgram(this->shaderProgram);
}

