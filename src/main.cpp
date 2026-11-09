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

//forward declarations
void frame(float delta_time);
SDL_Point draw(float x, float y , float z, std::function<Point(float, float, float)> fn);


int main() {
    r.create_window();

    bool running = true;
    Uint32 last = SDL_GetTicks();

    //event loop
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
        }  
        Uint32 now = SDL_GetTicks();
        float dt = (now - last) /1000.0f; //calculate delta time for rotation animations
        last = now;

        frame(dt); //run per frame function
    }
    return 0;
}

void frame(float delta_time) {
    angle += 1.0f * delta_time; //increment angle with dt

    r.clear();
    std::array<SDL_Point, 8> points; //create empty array to hold primed point values
    for (size_t i = 0; i < shape.vertices.size(); i++) {
        //set point
        points[i] = draw(shape.vertices[i].x, shape.vertices[i].y, shape.vertices[i].z, [&](float x, float y, float z) {
        return a.rotate_y(angle, x, y, z);
    });
    }

    r.clear(); //clear buffer

    //loop through shape edges and draw lines between them with new defined points
    for (const auto& [i,j] : shape.edges) {
        r.draw_line(points[i], points[j], {0, 255, 0, 255}); //i use green here for the colour
    }
    r.present();
}

/*projects point with our 2d to 3d formula and adds depth, takes func ptr to apply animation*/
SDL_Point draw(float x, float y , float z, std::function<Point(float x, float y, float z)> fn) {
    Point p2d = r.project(fn(x, y, z)); //get 2d point
    return r.to_screen(p2d.x, p2d.y); //translate to screen coords
}

