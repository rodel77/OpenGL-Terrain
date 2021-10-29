#include "Chunk.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>
#include <iostream>

#include <malloc.h>

#include "FastNoiseLite.h"

FastNoiseLite noise;
FastNoiseLite biome_noise;

void Chunk::create_mesh(){
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    biome_noise.SetNoiseType(FastNoiseLite::NoiseType_Cellular);
    biome_noise.SetCellularDistanceFunction(FastNoiseLite::CellularDistanceFunction_Hybrid);
    biome_noise.SetCellularReturnType(FastNoiseLite::CellularReturnType_CellValue);

    // ChunkSize * Faces * Vertices
    VertexData vertices[size * size * 2 * 3];
    // VertexData *vertices = (VertexData*) malloc(size * size * 2 * 3 * sizeof(VertexData));

    unsigned int vertex_id = 0;
    VertexData temp[6];
    for(int i = 0; i < (size)*(size); i++){
        float x = i%4;
        float z = (int)((float)i/4);
        temp[0] = add_vertex(x+1, z);
        temp[1] = add_vertex(x, z);
        temp[2] = add_vertex(x, z+1);
        temp[3] = add_vertex(x, z+1);
        temp[4] = add_vertex(x+1, z+1);
        temp[5] = add_vertex(x+1, z);

        glm::vec3 color = temp[1].color;
        glm::vec3 normal1 = glm::normalize(glm::cross(temp[1].position - temp[0].position, temp[2].position - temp[0].position));
        glm::vec3 normal2 = glm::normalize(glm::cross(temp[4].position - temp[3].position, temp[5].position - temp[3].position));

        for(int i = 0; i < 6; i++){
            temp[i].color  = color;
            temp[i].normal = i<3 ? normal1 : normal2;
            vertices[vertex_id++] = temp[i];
        }
    }

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size * size * 2 * 3 * sizeof(VertexData), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

VertexData Chunk::add_vertex(float x, float z){
    float vx = x*2;
    float vz = z*2;
    float nx = x + this->x * 4;
    float nz = z + this->z * 4;
    // float e = 1 * noise.GetNoise(10 * nx, 10 * nz)
    //         + .5 * noise.GetNoise(20 * nx, 20 * nz)
    //         + .25 * noise.GetNoise(40 * nx, 40 * nz);
    // e /= (1. + .5 + .25);
    // e *= 10;
    float e = noise.GetNoise(nx, nz) * 50
            + noise.GetNoise(20 * nx, 20 * nz)
            + noise.GetNoise(40 * nx, 40 * nz);

    VertexData vertex_data;
    float biome = noise.GetNoise(nx, nz);
    if(biome>0 && biome<.1) {
        vertex_data.color = glm::vec3(0.3f, 0.7f, 0.3f);
    }else{
        vertex_data.color = glm::vec3(0.9f, 0.9f, 0.7f);
    }
    vertex_data.color = glm::vec3(0.3f, 0.7f, 0.3f);

    if(e < -5){
        vertex_data.color = glm::vec3(.25f, .25f, 1.0f);
        e = noise.GetNoise(nx * 20, nz * 20)*1.5 - 4;
    }else if(e>10 && noise.GetNoise(nx, nz)>0.5){
        e *= 2;
        vertex_data.color = glm::vec3(.4f, .4f, .4f);
    }

    e *= .5;
    
    vertex_data.position = glm::vec3(vx, e, vz);
    return vertex_data;
}

void Chunk::render(){
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3 * 4*4 * 2);
}