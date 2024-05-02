#include "plateau_joueur.hpp"
#include <SDL2/SDL_ttf.h>

PlateauJoueur::PlateauJoueur(SDL_Renderer* renderer)
    : m_renderer(renderer), m_window(nullptr) {
    // Initialiser la fenêtre et autres éléments de l'interface utilisateur
    // Ici, vous pouvez utiliser la méthode initSDL() du code principal ou en créer une similaire.
}

PlateauJoueur::~PlateauJoueur() {
    // Nettoyer les ressources SDL utilisées par la classe PlateauJoueur
}

void PlateauJoueur::afficherInterface() {
    // Effacer l'écran
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_renderer);
    
    // Afficher le tableau
    SDL_Color textColor = {0, 0, 0, 255}; // Noir
    TTF_Font* font = TTF_OpenFont("fonts/UbuntuMono-R.ttf", 16);
    if (font == nullptr) {
        // Gérer l'erreur de chargement de la police
    }

    // Dessiner le tableau
    SDL_Rect cellRect = {10, 10, 100, 30}; // Rectangle pour chaque cellule
    SDL_Surface* textSurface = nullptr;
    SDL_Texture* textTexture = nullptr;

    // Afficher la première ligne
    std::vector<std::string> firstRow = {"Vide", "Argent", "Hotel1", "Hotel2", "Hotel3", "Hotel4"};
    for (int i = 0; i < 6; ++i) {
        textSurface = TTF_RenderText_Solid(font, firstRow[i].c_str(), textColor);
        textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
        SDL_RenderCopy(m_renderer, textTexture, NULL, &cellRect);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
        cellRect.x += 100; // Déplacer le rectangle à la prochaine colonne
    }

    // Réinitialiser la position pour la deuxième ligne
    cellRect.x = 10;
    cellRect.y += 30; // Descendre au prochain niveau

    // Afficher la deuxième ligne (Joueur 1)
    textSurface = TTF_RenderText_Solid(font, "Joueur 1", textColor);
    textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
    SDL_RenderCopy(m_renderer, textTexture, NULL, &cellRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    
    // Afficher la troisième ligne (Joueur 2)
    cellRect.y += 30; // Descendre encore au prochain niveau
    textSurface = TTF_RenderText_Solid(font, "Joueur 2", textColor);
    textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
    SDL_RenderCopy(m_renderer, textTexture, NULL, &cellRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    TTF_CloseFont(font);

    // Mettre à jour l'affichage
    SDL_RenderPresent(m_renderer);
}


void PlateauJoueur::gererEvenements() {
    // Gérer les événements des joueurs
}
