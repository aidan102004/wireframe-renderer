#pragma once
#include <SDL.h>

struct Color {
    int r;
    int g;
    int b;
    int a;
};


class Renderer {
private:
    int width = 800;
    int height = 800;
    Color COLOR = {0,0,0,0};
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
public:
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

    ~Renderer() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};