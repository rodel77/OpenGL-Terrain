#include "Chunk.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>
#include <iostream>

#include "FastNoiseLite.h"

FastNoiseLite noise;
FastNoiseLite biome_noise;

void Chunk::create_mesh(){
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    biome_noise.SetNoiseType(FastNoiseLite::NoiseType_Cellular);
    biome_noise.SetCellularDistanceFunction(FastNoiseLite::CellularDistanceFunction_Hybrid);
    biome_noise.SetCellularReturnType(FastNoiseLite::CellularReturnType_CellValue);

    float VertexData[size * size * 2 * 3];

    float vertices[size * size * 2 * 3 * 3];
    float normals[size * size * 2 * 3 * 3];
    float colors[size * size * 2 * 3 * 3];
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
    unsigned int colorid = 0;
    for(int i = 0; i < (size)*(size); i++){
        float x = i%4;
        float z = (int)((float)i/4);
        glm::vec3 color1, color2, color3, color;
        // glm::vec3 color(1.0);
        // color = glm::vec3(1.0, 0.0 ,0.0);
        glm::vec3 a = add_vertex(vertices, x+1, z, &index, color1);
        glm::vec3 b = add_vertex(vertices, x, z, &index, color2);
        glm::vec3 c = add_vertex(vertices, x, z+1, &index, color3);
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
        // color = color1;
        color = color1;
        // else color = color2;
        colors[colorid++] = color.x;
        colors[colorid++] = color.y;
        colors[colorid++] = color.z;
        colors[colorid++] = color.x;
        colors[colorid++] = color.y;
        colors[colorid++] = color.z;
        colors[colorid++] = color.x;
        colors[colorid++] = color.y;
        colors[colorid++] = color.z;


        a = add_vertex(vertices, x, z+1, &index, color1);
        b = add_vertex(vertices, x+1, z+1, &index, color2);
        c = add_vertex(vertices, x+1, z, &index, color3);
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
        // color = color1;
        // else color = color2;
        colors[colorid++] = color.x;
        colors[colorid++] = color.y;
        colors[colorid++] = color.z;
        colors[colorid++] = color.x;
        colors[colorid++] = color.y;
        colors[colorid++] = color.z;
        colors[colorid++] = color.x;
        colors[colorid++] = color.y;
        colors[colorid++] = color.z;
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


    glGenBuffers(1, &color_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(2);

// printf("%i\n", sizeof(color));
    // free(color);
}

glm::vec3 Chunk::add_vertex(float vertices[], float x, float z, unsigned int *index, glm::vec3 &color){
    // float vx = (x*2 + this->x * 8);
    // float vz = (z*2 + this->z * 8);
    float vx = x*2;
    float vz = z*2;
    float nx = x + this->x * 4;
    float nz = z + this->z * 4;
    // float e = 1 * noise.GetNoise(40 * nx, 40 * nz);
    float e = 1 * noise.GetNoise(10 * nx, 10 * nz)
            + .5 * noise.GetNoise(20 * nx, 20 * nz)
            + .25 * noise.GetNoise(40 * nx, 40 * nz);
    // float e = 1 * glm::perlin(glm::vec2(1 * nx, 1 * nz))
    //         + 1 * glm::perlin(glm::vec2(2 * nx, 2 * nz))
    //         + 1 * glm::perlin(glm::vec2(4 * nx, 4 * nz));
    e /= (1. + .5 + .25);
    // e = pow(e, .5);
    e *= 10;

    if(biome_noise.GetNoise(nx, nz)>0) {
        color = glm::vec3(0.3f, 0.7f, 0.3f);
    }else{
        color = glm::vec3(0.9f, 0.9f, 0.7f);
    }


    // printf("%f\n", noise.GetNoise(1 * nx, 1 * nz));

    // float vy = 
    // pow((noise.GetNoise((x + this->x * 4)*1, (z + this->z * 4)*1) +
    // (1/2)*noise.GetNoise((x + this->x * 4)*2, (z + this->z * 4)*2) +
    // (1/4)*noise.GetNoise((x + this->x * 4)*4, (z + this->z * 4)*4))/(1 + (1/2) + (1/4)), 1.5);
    vertices[(*index)++] = vx;
    vertices[(*index)++] = e;
    vertices[(*index)++] = vz;
    return glm::vec3(vx, e, vz);
}

void Chunk::render(){
    glBindVertexArray(vao);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(this->x * 8, 0, this->z * 8);
    glDrawArrays(GL_TRIANGLES, 0, 3 * 4*4 * 2);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
}