#include "shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vFile;
    std::ifstream fFile;

    vFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

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

    const char* vertRaw = vertexCode.c_str();
    const char* fragRaw = fragmentCode.c_str();

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // compile vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertRaw, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cerr << "Failed to compile Vertex shader file: " << vertexPath << std::endl;
        std::cerr << infoLog << std::endl;
    }

    // compile fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragRaw, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cerr << "Failed to compile fragment shader file: " << fragmentPath << std::endl;
        std::cerr << infoLog << std::endl;
    }

    // link shader program
    m_id = glCreateProgram();
    glAttachShader(m_id, vertex);
    glAttachShader(m_id, fragment);
    glLinkProgram(m_id);
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_id, 512, NULL, infoLog);
        std::cerr << "Error linking shader program using: " << vertexPath << " and " << fragmentPath << std::endl;
        std::cerr << infoLog << std::endl;
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use()
{
    glUseProgram(m_id);
}

void Shader::setBool(const std::string& name, bool value) const
{
    setInt(name, (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::setFloatMat4(const std::string& name, glm::mat4 value) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

unsigned int Shader::ID() const
{
    return m_id;
}
