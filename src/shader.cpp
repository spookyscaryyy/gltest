#include "shader.h"

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vFile;
    std::ifstream fFile;

    vFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    // read vertex shader file
    try
    {
        vFile.open(vertexPath);
        std::stringstream vStream;
        vStream << vFile.rdbuf();
        vFile.close();
        vertexCode = vStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cerr << "Failed to read Vertex shader file: " << vertexPath << std::endl;
    }

    // read fragment shader file
    try
    {
        fFile.open(fragmentPath);
        std::stringstream fStream;
        fStream << fFile.rdbuf();
        fFile.close();
        fragmentCode = fStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cerr << "Failed to read Fragment shader file: " << fragmentPath << std::endl;
    }

    const char *vertRaw = vertexCode.c_str();
    const char *fragRaw = fragmentCode.c_str();

    unsigned int vertex, fragment;

    // compile vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertRaw, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    // compile fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragRaw, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    // link shader program
    m_id = glCreateProgram();
    glAttachShader(m_id, vertex);
    glAttachShader(m_id, fragment);
    glLinkProgram(m_id);
    checkCompileErrors(m_id, "PROGRAM");
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use()
{
    glUseProgram(m_id);
}

void Shader::setBool(const std::string &name, bool value) const
{
    setInt(name, (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::setFloatMat4(const std::string &name, glm::mat4 value) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setFloatVec3(const std::string &name, glm::vec3 value) const
{
    glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, glm::value_ptr(value));
}

unsigned int Shader::ID() const
{
    return m_id;
}

void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    if (type != "PROGRAM")
    {
    }
}
