#include <SDL.h>
#include <cmath>
#include "renderer.h"
#include "animator.h"
#include <iostream>
#include <functional>
#include <array>

Renderer r;
Animator a;
float angle = 0.0f;

const std::array<std::pair<int,int>, 12> vertices = {{
    {0,1}, {0,2}, {1,3}, {2,3},   //front face
    {4,5}, {4,6}, {5,7}, {6,7},   //back face
    {0,4}, {1,5}, {2,6}, {3,7}    //connecting edges
}};

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

void draw_line(SDL_Point a, SDL_Point b, Color c);
void frame(float delta_time);
SDL_Point draw(float x, float y , float z, std::function<Point(float, float, float)> fn);
Point rotate_y(float x, float y, float z);
Point rotate_x(float x, float y, float z);
Point rotate_z(float x, float y, float z);

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
    for (size_t i = 0; i < vs.size(); i++) {
    points[i] = draw(vs[i].x, vs[i].y, vs[i].z, [&](float x, float y, float z) {
        return a.rotate_y(angle, x, y, z);
    });
    }

    r.clear();

    for (const auto& [i,j] : vertices) {
        draw_line(points[i], points[j], {0, 255, 0, 255});
    }
    r.present();
}

void draw_line(SDL_Point a, SDL_Point b, Color c) {
    SDL_SetRenderDrawColor(r.renderer, c.r, c.g, c.b, c.a);
    SDL_RenderDrawLine(r.renderer, a.x, a.y, b.x, b.y);
}

SDL_Point draw(float x, float y , float z, std::function<Point(float x, float y, float z)> fn) {
    Point p2d = r.project(fn(x, y, z));
    return r.to_screen(p2d.x, p2d.y);
    //r.draw_point(p.x, p.y, 20, {0, 255, 0, 255});
}

