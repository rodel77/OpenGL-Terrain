#include "World.h"
#include "Chunk.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void World::queue_chunk(int x, int z){
    auto chunk = new Chunk(x, z);
    // Chunk chunk(position.x, position.y);
    // Chunk *ptr = &chunk;
    // chunks.find(position);
    chunk->create_mesh();
    chunks[std::pair<int, int>(x, z)] = chunk;
    // printf("%i\n", has_chunk(x, y));
    // chunks.insert(position, &chunk);
    // chunks[position] = NULL;
}

void World::render(Shader &program){
    for(auto const& pair : chunks){
        auto transform = glm::translate(glm::mat4(1.0f), glm::vec3(pair.second->x * 8, 0, pair.second->z * 8));
        program.set_uniform_m4f("model", glm::value_ptr(transform));
        pair.second->render();
    }
}

bool World::has_chunk(int x, int z){
    return chunks.find(std::pair<int, int>(x, z))!=chunks.end();
}