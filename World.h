#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <map>
#include <queue>
#include <glm/glm.hpp>
#include "Chunk.h"
#include "Utils.h"
#include "Shader.h"

class World {
    public:
        void queue_chunk(int x, int z);
        void render(Shader &program);
        bool has_chunk(int x, int z);
        std::map<std::pair<int, int>, Chunk*> chunks;
    private:
        // std::queue<glm::ivec2> load_queue;
};

#endif