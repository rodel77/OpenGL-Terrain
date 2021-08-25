#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>

class Input{
    public:
        Input(){
            for(int i = 0; i < 322; i++) keys[i] = false;
        }

        void handle_event(SDL_Event *event) {
            if(event->type==SDL_KEYDOWN){
                keys[event->key.keysym.scancode] = true;
            }

            if(event->type==SDL_KEYUP){
                keys[event->key.keysym.scancode] = false;
            }
        }
        bool is_down(SDL_KeyCode key){
            return keys[SDL_GetScancodeFromKey(key)];
        }
    private:
        bool keys[322];
};

#endif