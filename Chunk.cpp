#include "Chunk.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>

#include "FastNoiseLite.h"

FastNoiseLite noise;

void Chunk::create_mesh(){
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    // vertices[0] = 0.0f;
    // vertices[1] = 0.0f;
    // vertices[2] = 0.0f;

    // vertices[3] = 1.0f;
    // vertices[4] = 0.0f;
    // vertices[5] = 0.0f;

    // vertices[6] = 0.0f;
    // vertices[7] = 0.0f;
    // vertices[8] = 1.0f;

    // 4 = 2
    // 6 = 4
    // 8 = 6
    // 10 = 8
    // 9 = 8
    // 12 = 18
    // 16 = 24



    unsigned int index = 0;
    unsigned int normalid = 0;
    for(int i = 0; i < (size)*(size); i++){
        float x = i%4;
        float z = (int)((float)i/4);
        glm::vec3 a = add_vertex(x+1, z, &index);
        glm::vec3 b = add_vertex(x, z, &index);
        glm::vec3 c = add_vertex(x, z+1, &index);
        glm::vec3 normal = glm::normalize(glm::cross(b - a, c - a));
        normals[normalid++] = normal.x;
        normals[normalid++] = normal.y;
        normals[normalid++] = normal.z;
        normals[normalid++] = normal.x;
        normals[normalid++] = normal.y;
        normals[normalid++] = normal.z;
        normals[normalid++] = normal.x;
        normals[normalid++] = normal.y;
        normals[normalid++] = normal.z;


        a = add_vertex(x, z+1, &index);
        b = add_vertex(x+1, z+1, &index);
        c = add_vertex(x+1, z, &index);
        normal = glm::normalize(glm::cross(b - a, c - a));
        normals[normalid++] = normal.x;
        normals[normalid++] = normal.y;
        normals[normalid++] = normal.z;
        normals[normalid++] = normal.x;
        normals[normalid++] = normal.y;
        normals[normalid++] = normal.z;
        normals[normalid++] = normal.x;
        normals[normalid++] = normal.y;
        normals[normalid++] = normal.z;
        // printf("%i %i\n", size * size * 2 * 3 * 3 * 2, index);
        // vertices[index++] = x+1;
        // vertices[index++] = noise.GetNoise((x+(4*this->x)+1)*10, (z+(4*this->z))*10);
        // vertices[index++] = z;

        // vertices[index++] = x;
        // vertices[index++] = noise.GetNoise((x+(4*this->x))*10, (z+(4*this->z))*10);
        // vertices[index++] = z;

        // vertices[index++] = x;
        // vertices[index++] = noise.GetNoise((x+(4*this->x))*10, (z+(4*this->z)+1)*10);
        // vertices[index++] = z+1;

        // vertices[index++] = x+1;
        // vertices[index++] = noise.GetNoise((x+(4*this->x)+1)*10, (z+(4*this->z))*10);
        // vertices[index++] = z;

        // vertices[index++] = x+1;
        // vertices[index++] = noise.GetNoise((x+(4*this->x)+1)*10, (z+(4*this->z)+1)*10);
        // vertices[index++] = z+1;

        // vertices[index++] = x;
        // vertices[index++] = noise.GetNoise((x+(4*this->x))*10, (z+(4*this->z)+1)*10);
        // vertices[index++] = z+1;

        // printf("%i\n", index);
    }

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &normal_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(1);
}

glm::vec3 Chunk::add_vertex(float x, float z, unsigned int *index){
    float vx = (x + this->x * 4);
    float vy = noise.GetNoise((x + this->x * 4)*20, (z + this->z * 4)*20);
    float vz = (z + this->z * 4);
    vertices[(*index)++] = vx;
    vertices[(*index)++] = vy;
    vertices[(*index)++] = vz;
    return glm::vec3(vx, vy, vz);
}

void Chunk::render(){
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3 * 4*4 * 2);
}