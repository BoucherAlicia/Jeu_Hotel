#include "case.hpp"

Case::Case() {
    // Initialisation des tableaux à des valeurs par défaut 
    for (int i = 1; i < 30; ++i) {
        number[i] = i;
        // Calcul des coordonnées x et y en fonction du numéro de la case
        if (number[i] >= 0 && number[i] <= 7) {
            x[i] = 150;
            y[i] = 450 - 50 * number[i];
        } else if (number[i] >= 8 && number[i] <= 15) {
            x[i] = 200 + 50 * (number[i] - 8);
            y[i] = 100;
        } else if (number[i] >= 16 && number[i] <= 22) {
            x[i] = 550;
            y[i] = 100 + 50 * (number[i] - 15);
        } else{
            x[i] = 550 - 50 * (number[i] - 22);
            y[i] = 450;
        }
        
    }
    number[0] = 0; // Les numéros de case commencent à 0
    x[0] = 150;
    y[0] = 450;
    //std::cout << "La case numéro " << 0 << " est aux coordonnées : (" << x[0] << ", " << y[0] << ")." << std::endl;
}

void Case::display(SDL_Renderer* renderer, TTF_Font* font, int caseNumber) const {
    // Dessiner le rectangle blanc représentant le contour de la case
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Couleur blanche
    SDL_Rect outerRect = { x[caseNumber], y[caseNumber], width, height }; // Rectangle de la taille de la case
    SDL_RenderDrawRect(renderer, &outerRect);

    // Dessiner le numéro de la case au-dessus du rectangle
    SDL_Rect textRect;
    textRect.w = 20;
    textRect.h = 20;
    SDL_Color textColor = { 100, 100, 255 }; // Couleur du texte (bleu)
    std::string numberString = std::to_string(caseNumber + 1); // Ajouter 1 pour afficher le numéro correct

    // Position du texte
    if (caseNumber >= 0 && caseNumber <= 6) {
        textRect.x = x[caseNumber] - 30; // Ajustez la position du texte à gauche de la case
        textRect.y = y[caseNumber];
    } else if (caseNumber >= 16 && caseNumber <= 22) {
        textRect.x = x[caseNumber] + width + 10; // Ajustez la position du texte à droite de la case
        textRect.y = y[caseNumber];
    } else {
        textRect.x = x[caseNumber] + (width / 2) - 10; // Ajustez la position du texte au centre de la case
        textRect.y = y[caseNumber] - 20; // Placez le texte au-dessus de la case
    }

    // Convertir le texte en surface et en texture
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, numberString.c_str(), textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    // Afficher le texte sur le renderer
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    // Nettoyer la mémoire
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}




const int Case::getCase(int index) const {
    if (index >= 0 && index < 30) {
        return number[index];
    } else {
        // Gérer l'erreur ou renvoyer une valeur par défaut
        return -1;
    }
}

