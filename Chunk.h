#ifndef CHUNK_H
#define CHUNK_H

#include <glm/glm.hpp>


struct VertexData {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
};

class Chunk{
    public:
        Chunk(int x, int z) {
            this->x = x;
            this->z = z;
        }

        // float vertices[size * size * 2 * 3 * 3];
        // float normals[size * size * 2 * 3 * 3];
        // float color[size * size * 2 * 3 * 3];
        bool has_mesh = false;
        unsigned int vao, vbo, normal_buffer, color_buffer;
        int x, z;

        void create_mesh();
        void render();
    private:
        VertexData add_vertex(float x, float z);
};

#endif