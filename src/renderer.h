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

    void draw_point(int x, int y, int size, Color c) {
        SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
        SDL_Rect rect = { x - size / 2, y - size / 2, size, size };
        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_Point to_screen(float x, float y, float scale = SCALE) {
        return { (int)(x * scale) + width / 2, (int)(-y * scale) + height / 2 };
    }

    Point project(const Point& p) {
        float sx = p.x/p.z;
        float sy = p.y/p.z;
        return {sx,sy};
    }

    ~Renderer() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};