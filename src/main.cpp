#include <SDL.h>
#include <cmath>
#include "renderer.h"
#include <iostream>
#include <functional>
#include <array>

Renderer r;
float angle = 0.0f;

const std::array<Point, 8> vs = {{
    { 0.5f,  0.5f, 0.5f},
    {-0.5f,  0.5f, 0.5f},
    { 0.5f, -0.5f, 0.5f},
    {-0.5f, -0.5f, 0.5f},

    { 0.5f,  0.5f, -0.5f},
    {-0.5f,  0.5f, -0.5f},
    { 0.5f, -0.5f, -0.5f},
    {-0.5f, -0.5f, -0.5f}
}};

void frame(float delta_time);
void draw(float x, float y , float z, std::function<Point(float x, float y, float z)> fn);
Point rotate(float x, float y, float z);

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

        frame(dt);
    }
    return 0;
}

void frame(float delta_time) {
    angle += 1.0f * delta_time;

    r.clear();
    for (const auto& v : vs) {
        draw(v.x, v.y, v.z, rotate);
    }
    r.present();
}

void draw(float x, float y , float z, std::function<Point(float x, float y, float z)> fn) {
    Point p2d = r.project(fn(x, y, z));
    SDL_Point p = r.to_screen(p2d.x, p2d.y);
    r.draw_point(p.x, p.y, 20, {0, 255, 0, 255});
}

Point rotate(float x, float y, float z) {
    float c = std::cos(angle), s = std::sin(angle);
    float xp = z * s - x * c;
    float zp = z * c + x * s;
    return {xp, y, zp};
}
