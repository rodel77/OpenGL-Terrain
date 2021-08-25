#include "World.h"
#include "Chunk.h"

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

void World::render(){
    for(auto const& pair : chunks){
        pair.second->render();
    }
}

bool World::has_chunk(int x, int z){
    return chunks.find(std::pair<int, int>(x, z))!=chunks.end();
}