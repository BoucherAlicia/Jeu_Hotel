#ifndef PLATEAU_JOUEUR_HPP
#define PLATEAU_JOUEUR_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>

class PlateauJoueur {
public:
    PlateauJoueur(SDL_Renderer* renderer);
    ~PlateauJoueur();

    // Méthodes pour afficher l'interface utilisateur, gérer les événements, etc.
    void afficherInterface();
    void gererEvenements();

private:
    SDL_Renderer* m_renderer;
    std::vector<std::string> firstRow;
    TTF_Font* m_font; // Déclaration de la police de caractères
    SDL_Window* m_window;
};

#endif // PLATEAU_JOUEUR_HPP
