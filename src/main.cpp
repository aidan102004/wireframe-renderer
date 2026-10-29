#include <SDL.h>
#include "renderer.h"
#include <iostream>

int main() {
    Renderer r;
    r.create_window();

    bool running = true;

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
        }  
        r.clear();
        SDL_Point p = r.to_screen(1.0f, 1.0f);
        //std::cout << p.x << p.y << std::endl;
        r.draw_point(p.x, p.y, 20, {255, 255, 255, 255});
        r.present();
    }
    return 0;
}

