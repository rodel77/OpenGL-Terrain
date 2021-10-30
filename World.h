#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <map>
#include <queue>
#include <mutex>
#include <glm/glm.hpp>
#include "Chunk.h"
#include "Utils.h"
#include "Shader.h"
#include "readerwriterqueue.h"

class World {
    public:
        World();
        ~World();
        void queue_chunk(int x, int z);
        void render(Shader &program);
        bool has_chunk(int x, int z);
        std::map<std::pair<int, int>, Chunk*> chunks;
        std::mutex chunk_mutex;
        bool loaded = true;

        moodycamel::ReaderWriterQueue<Chunk*> chunk_queue;
    private:
        // std::queue<glm::ivec2> load_queue;
};

static float min(float a, float b) { return a < b ? a : b; }
static float max(float a, float b) { return a > b ? a : b; }

#endif