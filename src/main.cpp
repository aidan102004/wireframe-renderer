#include <SDL.h>
#include "renderer.h"

int main() {
    Renderer renderer;
    renderer.create_window();

    bool running = true;

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type = SDL_QUIT) running = false;
        }  
        renderer.clear();
        //todo
        renderer.present();
    }
    return 0;
}

