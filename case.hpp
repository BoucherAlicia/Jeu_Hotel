#ifndef CASE_HPP
#define CASE_HPP


#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Classe représentant une case sur le plateau
class Case {
private:
    int number[29]; // Numéro de la case
    int x[29]; // Coordonnée x
    int y[29]; // Coordonnée y

    int occupyingPlayer[29]; // Joueur occupant la case (0 si non occupée)
    static const int width = 50;
    static const int height = 50;


    SDL_Renderer* renderer;
    TTF_Font* font; // Déclaration de la police de caractères



public:
    Case();
    
    // Méthodes pour récupérer les coordonnées x et y d'une case spécifique
    int getX(int numeroCase) const { return x[numeroCase]; }
    int getY(int numeroCase) const { return y[numeroCase]; }

    // Méthode pour afficher les informations de la case
    void display(SDL_Renderer* renderer, TTF_Font* font, int caseNumber) const;
    const int getCase(int index) const;


};
#endif