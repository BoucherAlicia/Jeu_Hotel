#include "case.hpp"

void Case::display(SDL_Renderer* renderer, TTF_Font* font) const {
    // Dessiner le rectangle blanc représentant le contour de la case
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Couleur blanche
    SDL_Rect outerRect = { x - 2, y - 2, width + 4, height + 4 }; // Rectangle légèrement plus grand
    SDL_RenderDrawRect(renderer, &outerRect);

    // Dessiner le rectangle représentant la case à l'intérieur du rectangle blanc
    SDL_Rect innerRect = { x, y, width, height };
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Couleur noire
    SDL_RenderDrawRect(renderer, &innerRect);

    // Dessiner le numéro de la case au-dessus du rectangle
    SDL_Rect textRect;
    textRect.w = 20;
    textRect.h = 20;
    SDL_Color textColor = { 100, 100, 255 }; // Couleur du texte (bleu)
    std::string numberString = std::to_string(number);
    
    // Position du texte
    if (number >= 1 && number <= 7) {
        textRect.x = x - 30; // Ajustez la position du texte à gauche de la case
        textRect.y = y;
    } else if (number >= 17 && number <= 23) {
        textRect.x = x + width + 10; // Ajustez la position du texte à droite de la case
        textRect.y = y;
    } else {
        textRect.x = x + (width / 2) - 10; // Ajustez la position du texte au centre de la case
        textRect.y = y - 20; // Placez le texte au-dessus de la case
    }

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, numberString.c_str(), textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}
