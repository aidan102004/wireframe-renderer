#include <SDL.h>
#include <cmath>
#include "renderer.h"
#include <iostream>

Renderer r;
float angle = 0.0f;

void frame(float delta_time);

int main() {
    r.create_window();

    bool running = true;
    Uint32 last = SDL_GetTicks();
    float dz = 0.0f;

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
        }  
        Uint32 now = SDL_GetTicks();
        float dt = (now - last) /1000.0f;
        last = now;

        dz += 1.0f *dt;
        r.clear();
        
        Point p2d = r.project({1.0f, 0.0f, 1.0f + dz});
        SDL_Point p = r.to_screen(p2d.x, p2d.y);
        r.draw_point(p.x, p.y, 20, {0, 255, 0, 255});
        r.present();
        //frame(dt);
    }
    return 0;
}

void frame(float delta_time) {
    angle += 1.0f * delta_time;

    float c = std::cos(angle), s = std::sin(angle);
    float x = 0.0f, y = 1.0f, z = 0.0f;
    float xp = x * c - y * s;
    float yp = x * s + y * c;
    r.clear();
    Point p2d = r.project({xp, yp, z});
    SDL_Point p = r.to_screen(p2d.x, p2d.y);
    r.draw_point(p.x, p.y, 20, {0, 255, 0, 255});
    r.present();
}
