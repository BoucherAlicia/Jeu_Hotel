#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Classe représentant une case sur le plateau
class Case {
private:
    int number; // Numéro de la case
    int x; // Coordonnée x
    int y; // Coordonnée y
    static const int width = 50;
    static const int height = 50;


    SDL_Renderer* renderer;
    TTF_Font* font; // Déclaration de la police de caractères



public:
    Case(int num, int xPos, int yPos) : number(num), x(xPos), y(yPos) {};

    // Méthode pour afficher les informations de la case
    void display(SDL_Renderer* renderer, TTF_Font* font) const;
};
