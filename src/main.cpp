#include <SDL.h>
#include <cmath>
#include "renderer.h"
#include "animator.h"
#include "shape.h"
#include <iostream>
#include <functional>
#include <array>

Renderer r;
Animator a;
Shape shape = make_pyramid();
float angle = 0.0f;


void frame(float delta_time);
SDL_Point draw(float x, float y , float z, std::function<Point(float, float, float)> fn);


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
    std::array<SDL_Point, 8> points;
    for (size_t i = 0; i < shape.vertices.size(); i++) {
        points[i] = draw(shape.vertices[i].x, shape.vertices[i].y, shape.vertices[i].z, [&](float x, float y, float z) {
        return a.rotate_y(angle, x, y, z);
    });
    }

    r.clear();

    for (const auto& [i,j] : shape.edges) {
        r.draw_line(points[i], points[j], {0, 255, 0, 255});
    }
    r.present();
}

SDL_Point draw(float x, float y , float z, std::function<Point(float x, float y, float z)> fn) {
    Point p2d = r.project(fn(x, y, z));
    return r.to_screen(p2d.x, p2d.y);
}

