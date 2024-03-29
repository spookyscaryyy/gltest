#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <assimp/scene.h>

#include "shader.h"

typedef struct _vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 tex_coords;
} Vertex;

typedef struct _texture {
    unsigned int id;
    aiTextureType type;
    std::string path;
} Texture;

class Mesh {
    public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void draw(Shader &shader);
    
    private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    unsigned int VAO, VBO, EBO;

    void setup_mesh();
};

#endif