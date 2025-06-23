//
// Created by theo on 6/23/25.
//

#ifndef SHDR_H
#define SHDR_H


#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

std::string get_file_content(const char* file_path);

class Shader {
public:
    GLuint ID;
    Shader(const char* vertexFile, const char* fragmentFile);
    void Activate();
    void Delete();
};

#endif
