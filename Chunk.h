#ifndef CHUNK_H
#define CHUNK_H

#include <glm/glm.hpp>

class Chunk{
    public:
        Chunk(int x, int z) {
            this->x = x;
            this->z = z;
        }
        ~Chunk(){
            printf("Destroying chunk!");
        }
        const static int size = 4;

        float vertices[size * size * 2 * 3 * 3];
        float normals[size * size * 2 * 3 * 3];
        unsigned int vao, vbo, normal_buffer;
        int x, z;

        void create_mesh();
        void render();
    private:
        glm::vec3 add_vertex(float x, float z, unsigned int *index);
};

#endif