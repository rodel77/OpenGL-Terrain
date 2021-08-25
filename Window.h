#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>

class Window {
    public:
        void init();
        void destroy();
        void resize();

        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_GLContext context;
};

#endif