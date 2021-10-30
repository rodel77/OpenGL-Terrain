#include "World.h"
#include "Chunk.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "SDL.h"

static int async(void *ptr){
    World* world = (World*)ptr;
    while(world->loaded){
        Chunk *chunk = NULL;
        while(world->chunk_queue.try_dequeue(chunk)){
            if(chunk->mesh_status==0){
                chunk->create_mesh();
            }
        }
    }
    return 0;
}

World::World(){
    // queue_chunk(0, 0);
    // int x = 0;
    // int z = 0;
    // auto chunk = new Chunk(x, z);
    // // chunk->create_mesh();
    // chunks[std::pair<int, int>(x, z)] = chunk;
    SDL_Thread *terrain_thread = SDL_CreateThread(async, "Generator", this);
    // SDL_Thread *terrain_thread2 = SDL_CreateThread(async, "Generator2", this);
    // SDL_Thread *terrain_thread3 = SDL_CreateThread(async, "Generator3", this);
    // SDL_CreateThread(async, "test", NULL);
}

World::~World(){
    loaded = false;
}

void World::queue_chunk(int x, int z){
    auto chunk = new Chunk(x, z);

    // std::lock_guard<std::mutex> guard(chunk_mutex);
    if(chunk_queue.try_enqueue(chunk)){
        chunks[std::pair<int, int>(x, z)] = chunk;
    }else{
        delete chunk;
    }
}

void World::render(Shader &program){
    for(auto const& pair : chunks){
        auto transform = glm::translate(glm::mat4(1.0f), glm::vec3(pair.second->x * CHUNK_SIZE, 0, pair.second->z * CHUNK_SIZE));
        program.set_uniform_m4f("model", glm::value_ptr(transform));
        pair.second->render();
    }
}

bool World::has_chunk(int x, int z){
    return chunks.find(std::pair<int, int>(x, z))!=chunks.end();
}