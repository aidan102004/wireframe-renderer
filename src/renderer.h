#pragma once
#include <SDL.h>
#include "point.h"

struct Color {
    int r;
    int g;
    int b;
    int a;
};


class Renderer {
private:
    //constants
    static constexpr int width = 800;
    static constexpr int height = 800;
    static constexpr float SCALE = 400.0f;
    Color COLOR = {0,0,0,0};
public:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    void create_window() {
        SDL_Init(SDL_INIT_VIDEO);
        window = SDL_CreateWindow("Wireframe", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    }

    void clear() {
        SDL_SetRenderDrawColor(renderer, COLOR.r, COLOR.g, COLOR.b, COLOR.a);
        SDL_RenderClear(renderer);
    }

    void present() { SDL_RenderPresent(renderer); }

    /*draws a single point... i actually dont use this anymore because we just draw lines, not the points themselves*/
    void draw_point(int x, int y, int size, Color c) {
        SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
        SDL_Rect rect = { x - size / 2, y - size / 2, size, size };
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderDrawLine(renderer, 100, 100, 700, 500);
    }

    /*draws line between 2 given points with a given colour*/
    void draw_line(SDL_Point a, SDL_Point b, Color c) {
        SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
        SDL_RenderDrawLine(renderer, a.x, a.y, b.x, b.y);
    }

    /*world space to screen space calcualtion*/
    SDL_Point to_screen(float x, float y, float scale = SCALE) {
        return { (int)(x * scale) + width / 2, (int)(-y * scale) + height / 2 };
    }

    Point project(const Point& p, float camera_dist = 2.0f) {
        float depth = p.z + camera_dist; //add camera dist to z 
        //calculate x' and y'
        float sx = p.x/depth;
        float sy = p.y/depth;
        return {sx,sy}; //return Point obj
    }

    ~Renderer() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};