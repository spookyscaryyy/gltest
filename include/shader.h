#ifndef SHADER_H
#define SHADER_H

#include <glad/gl.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
    private:

    unsigned int m_id;
    void checkCompileErrors(unsigned int shader, std::string type);

    public:
    Shader(const char* vertexPath, const char* fragmentPath);

    void use();
    unsigned int ID() const;
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setFloatMat4(const std::string& name, glm::mat4 value) const;
    void setFloatVec3(const std::string& name, glm::vec3 value) const;

};

#endif