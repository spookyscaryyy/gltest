#ifndef SHADER_H
#define SHADER_H

#include <glad/gl.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
    private:

    unsigned int m_id;

    public:
    Shader(const char* vertexPath, const char* fragmentPath);

    void use();
    unsigned int ID() const;
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;

};

#endif