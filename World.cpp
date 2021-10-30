#include "World.h"
#include "Chunk.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "SDL.h"

static int async(void *ptr){
    Chunk* chunk = (Chunk*)ptr;
    chunk->create_mesh();
    // while(true){
    //     // world->chunk_queue_lock.lock();
    //     while(world->chunk_queue.size()>0){
    //         auto coords = world->chunk_queue.front();
    //         auto chunk = new Chunk(coords.first, coords.second);
    //         chunk->create_mesh();
    //         printf("Gen mesh\n");
    //         // world->chunk_lock.lock();
    //         world->chunks[coords] = chunk;
    //         // world->chunk_lock.unlock();
    //         world->chunk_queue.pop();
    //     }
    //     // world->chunk_queue_lock.unlock();
    // }
    return 0;
}

World::World(){
    // queue_chunk(0, 0);
    // int x = 0;
    // int z = 0;
    // auto chunk = new Chunk(x, z);
    // // chunk->create_mesh();
    // chunks[std::pair<int, int>(x, z)] = chunk;
    // SDL_Thread *terrain_thread = SDL_CreateThread(async, "Generator", chunk);
    // SDL_CreateThread(async, "test", NULL);
}

World::~World(){
}

void World::queue_chunk(int x, int z){
    auto chunk = new Chunk(x, z);
    chunk->create_mesh();
    chunks[std::pair<int, int>(x, z)] = chunk;
    // std::lock_guard<std::mutex> lock(chunk_queue_lock);
    // chunk_queue.push(std::pair<int, int>(x, z));
    // Chunk chunk(position.x, position.y);
    // Chunk *ptr = &chunk;
    // chunks.find(position);
    // printf("%i\n", has_chunk(x, y));
    // chunks.insert(position, &chunk);
    // chunks[position] = NULL;
}

void World::render(Shader &program){
    for(auto const& pair : chunks){
        if(!pair.second->has_mesh) continue;
        auto transform = glm::translate(glm::mat4(1.0f), glm::vec3(pair.second->x * CHUNK_SIZE, 0, pair.second->z * CHUNK_SIZE));
        program.set_uniform_m4f("model", glm::value_ptr(transform));
        pair.second->render();
    }
}

bool World::has_chunk(int x, int z){
    return chunks.find(std::pair<int, int>(x, z))!=chunks.end();
}