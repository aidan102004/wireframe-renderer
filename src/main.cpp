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
        Point p2d = r.project({0.0f, 1.0f, 0.0f});
        SDL_Point p = r.to_screen(p2d.x, p2d.y);
        //std::cout << p.x << p.y << std::endl;
        r.draw_point(p.x, p.y, 20, {0, 255, 0, 255});
        r.present();
    }
    return 0;
}

