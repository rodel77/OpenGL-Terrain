#include "Window.h"

#include <SDL.h>
#include <SDL_opengl.h>
#include <iostream>

void Window::init(){
    SDL_Init(SDL_INIT_VIDEO);
    if(SDL_CreateWindowAndRenderer(640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL, &window, &renderer)==-1){
        printf("An error ocurred initializing window %s\n", SDL_GetError());
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

    context = SDL_GL_CreateContext(window);

    printf("OpenGL: %s\n", glGetString(GL_VERSION));
}

void Window::resize(){
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    glViewport(0, 0, w, h);
}

void Window::destroy(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}