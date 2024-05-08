// main.cpp
#include <SDL2/SDL.h>
#include "plateau.hpp"
#include "terrain.hpp"
#include "joueur.hpp"
#include "case.hpp"



int main() {
    int argentInitial = 25000;
    // Création des joueurs
    Joueur joueur1("Joueur 1", argentInitial);
    Joueur joueur2("Joueur 2", argentInitial);
/*---------------------------------------------------------------------------------------------------------------------*/
    //Tests terrain.cpp
    Terrain terrain;
    int numerocase = 1;
    terrain.getTerrainAdjacent(numerocase);
    terrain.occupe(numerocase);
    terrain.getTerrainAdjacent(numerocase);
    numerocase = 7;
    terrain.getTerrainAdjacent(numerocase);
/*---------------------------------------------------------------------------------------------------------------------*/
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        // Gestion d'erreur si l'initialisation de SDL échoue
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Hotel Deluxe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1500, 900, SDL_WINDOW_SHOWN);
    if (!window) {
        // Gestion d'erreur si la création de la fenêtre échoue
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to create SDL window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        // Gestion d'erreur si la création du renderer échoue
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to create SDL renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Create a Renderer instance
    Renderer gameRenderer(renderer, 800, 600);

    


    // Main loop
    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Render the game
        gameRenderer.renderGame();
    }
    
    
    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();


    return 0;
}
