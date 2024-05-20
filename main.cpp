//main.cpp
#include "hotel.hpp"
#include "terrain.hpp"
#include "jeu.hpp"
#include "plateau.hpp"

int main() {

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Hotel Deluxe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1500, 900, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to create SDL window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to create SDL renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Create a Renderer instance
    Renderer gameRenderer(renderer, 800, 600);

    // Jouer la partie
    jouerPartie(renderer, gameRenderer);

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
