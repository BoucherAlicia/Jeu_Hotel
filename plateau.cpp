// plateau.cpp

#include "plateau.hpp"
#include <chrono>
#include <thread>

Renderer::Renderer(SDL_Renderer* m_renderer, int width, int height)
    : m_renderer(m_renderer), m_width(width), m_height(height) {
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    }
    m_font = TTF_OpenFont( "fonts/UbuntuMono-R.ttf", 14 );
    if( m_font == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    m_font2 = TTF_OpenFont( "fonts/UbuntuMono-R.ttf", 20 );
    if( m_font2 == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    initTrackRects();
    initHotelNames();
}

Renderer::~Renderer() {
   // SDL_Destroyrenderer(m_renderer);
}

//------------------------------------------------------------------------------------------------------------//
void Renderer::initTrackRects() {
    // Exemple de circuit rectangulaire simple
    
    // Top
    m_trackRects.push_back({150, 100, 400, 50});
    // Bottom
    m_trackRects.push_back({150, 450, 400, 50});
    // Right
    m_trackRects.push_back({550, 100, 50, 400});    
    // Left
    m_trackRects.push_back({150, 100, 50, 400});

    // Rectangle pour l'emplacement de l'hôtel 1
    m_hotelRects.push_back({10, 500, 140, 90});

    // Rectangle pour l'emplacement de l'hôtel 2
    m_hotelRects.push_back({10, 10, 140, 90});

    // Rectangle pour l'emplacement de l'hôtel 3
    m_hotelRects.push_back({600, 10, 140, 90});

    // Rectangle pour l'emplacement de l'hôtel 4
    m_hotelRects.push_back({600, 500, 140, 90});
    
    // Rectangles pour l'emplacement de l'hôtel 1
    m_hotelRects.push_back({10, 300, 140, 200});
    m_hotelRects.push_back({150, 500, 250, 90});

    // Rectangle pour l'emplacement de l'hôtel 2
    m_hotelRects.push_back({10, 100, 140, 200});
    m_hotelRects.push_back({150, 10, 225, 90});

    // Rectangle pour l'emplacement de l'hôtel 3
    m_hotelRects.push_back({375, 10, 225, 90});
    m_hotelRects.push_back({600, 100, 140, 200});

    // Rectangle pour l'emplacement de l'hôtel 4
    m_hotelRects.push_back({600, 300, 140, 200});
    m_hotelRects.push_back({375, 500, 225, 90});

    // Rectangle pour mettre le titre rouge
    m_hotelRects.push_back({750, 10, 40, 580});

}

//------------------------------------------------------------------------------------------------------------//

void Renderer::initHotelNames() {
    // Initialisation des noms d'hôtels pour les emplacements autour du circuit
    m_hotelNames.push_back("Hotel1");
    m_hotelNames.push_back("Hotel2");
    m_hotelNames.push_back("Hotel3");
    m_hotelNames.push_back("Hotel4");
    m_hotelNames.push_back(" ");
    m_hotelNames.push_back(" ");
    m_hotelNames.push_back(" ");
    m_hotelNames.push_back(" ");
    m_hotelNames.push_back(" ");
    m_hotelNames.push_back(" ");
    m_hotelNames.push_back(" ");
    m_hotelNames.push_back(" ");
    m_hotelNames.push_back("Hotel Deluxe BOUCHER-ELMORR");
}

//------------------------------------------------------------------------------------------------------------//

void Renderer::renderGame(const Joueur& joueurs, const std::vector<std::string>& phrases, int resultat_de, int resultat_de_special, const std::vector<int>& typeHotel, std::vector<int>& entrees, const std::vector<bool>& tableauBool, const std::vector<int>& occupTerrain) {
    //Effacer l'écran
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_renderer);
    renderTrack(); //affichage circuit

    renderDe(resultat_de, resultat_de_special);
    
    //affiche les hotels statiques et achetés
    renderHotels();
    renderHotelAffiche(typeHotel);
    renderEntreeAffiche(entrees);
    
    renderTable(joueurs, occupTerrain, typeHotel); //affiche le tableau en bas
    renderBanqueAffiche(); //banque
    renderMairieAffiche(); //mairie
    
    //renderDe(resultat_de, resultat_de_special); //affiche le dé central + boutons dés
    renderCases();
    afficherPion(joueurs);
    renderTerminal(phrases);

    //ajouter ici renderHotel et renderEntree si ca glitch
    SDL_RenderPresent(m_renderer);

}

//------------------------------------------------------------------------------------------------------------//

void Renderer::renderTrack() {
    // Rendu du circuit
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255); // Noir
    for (const auto& rect : m_trackRects) 
    {
       SDL_RenderFillRect(m_renderer, &rect);
    }

    // Rendu du rectangle bleu (DEPART) en bas à gauche
    SDL_Rect startRect = {150, 450, 50, 50};
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, 255); // Bleu
    SDL_RenderFillRect(m_renderer, &startRect);
    // Rendu du texte "Départ" sur le rectangle bleu
    SDL_Color textColor = {255, 255, 255, 255}; // Blanc
    SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, "DEPART", textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
    SDL_Rect textRect = {150 + 50 / 2 - textSurface->w / 2, 450 + 50 / 2 - textSurface->h / 2, textSurface->w, textSurface->h};
    SDL_RenderCopy(m_renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

//------------------------------------------------------------------------------------------------------------//

void Renderer::renderHotels() {
    // Dessiner et remplir les rectangles des hôtels avec des couleurs pastel
    for (int i = 0; i < m_hotelRects.size(); ++i) {
        const auto& rect = m_hotelRects[i];

        // Choisir la couleur de remplissage en fonction de l'index de l'hôtel
        SDL_Color fillColor;
        switch (i) {
            case 0: // Hotel1 : Rose pastel
                fillColor = {255, 192, 203, 255}; // RVB pour le rose pastel
                break;
            case 1: // Hotel2 : Bleu pastel
                fillColor = {173, 216, 230, 255}; // RVB pour le bleu pastel
                break;
            case 2: // Hotel3 : Violet pastel
                fillColor = {221, 160, 221, 255}; // RVB pour le violet pastel
                break;
            case 3: // Hotel4 : Vert pastel
                fillColor = {144, 238, 144, 255}; // RVB pour le vert pastel
                break;

            case 4: // Hotel1 : Rose pastel
            case 5:
                fillColor = {255, 192, 203, 255}; // RVB pour le rose pastel
                break;
            case 6: // Hotel2 : Bleu pastel
            case 7:
                fillColor = {173, 216, 230, 255}; // RVB pour le bleu pastel
                break;
            case 8: // Hotel3 : Violet pastel
            case 9:
                fillColor = {221, 160, 221, 255}; // RVB pour le violet pastel
                break;
            case 10: // Hotel4 : Vert pastel
            case 11:
                fillColor = {144, 238, 144, 255}; // RVB pour le vert pastel
                break;
            case 12:
                fillColor = {255, 50, 50, 255}; // RVB pour le rouge pastel
                break;
            
            default:
                fillColor = {255, 255, 255, 255}; // Blanc par défaut
                break;
        }

        // Remplir le rectangle avec la couleur correspondante
        SDL_SetRenderDrawColor(m_renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
        SDL_RenderFillRect(m_renderer, &rect);

        // Dessiner le contour du rectangle
        //SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255); // Noir
        SDL_RenderDrawRect(m_renderer, &rect);

        // Afficher le nom de l'hôtel à l'intérieur du rectangle
        SDL_Color textColor = {0, 0, 0, 255}; // Noir
        
        int textWidth, textHeight;
        SDL_Rect textRect;
        SDL_Surface* textSurface;
        SDL_Texture* textTexture;
        if (i == 12)
        {
            textSurface = TTF_RenderText_Solid(m_font2, m_hotelNames[i].c_str(), textColor);
            TTF_SizeText(m_font2, m_hotelNames[i].c_str(), &textWidth, &textHeight);
            textRect = {rect.x + (rect.w - textWidth) / 2, rect.y + (rect.h - textHeight) / 2, textWidth, textHeight*2};
            textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
            // Rotation du texte à afficher de 90 degrés (sens horaire)
            SDL_RenderCopyEx(m_renderer, textTexture, NULL, &textRect, 90, NULL, SDL_FLIP_NONE);

        } 
        else {
            textSurface = TTF_RenderText_Solid(m_font, m_hotelNames[i].c_str(), textColor);
            TTF_SizeText(m_font, m_hotelNames[i].c_str(), &textWidth, &textHeight);
            textRect = {rect.x + (rect.w - textWidth) / 2, rect.y + (rect.h - textHeight) / 2, textWidth, textHeight};
            textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
            SDL_RenderCopy(m_renderer, textTexture, NULL, &textRect);
        } 
        
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }
}

//------------------------------------------------------------------------------------------------------------//

void Renderer::renderDe(int resultat_de, int resultat_de_special) {
    // Jouer le dé
    SDL_SetRenderDrawColor(m_renderer, 173, 216, 230, 255); // Bleu clair
    SDL_Rect buttonRect = {800, 10, 150, 50}; // Rectangle autour du texte "Jouer le dé"
    SDL_RenderFillRect(m_renderer, &buttonRect);

    SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, "Jouer le de", {0, 0, 0, 255}); // Noir
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
    SDL_Rect textRect = {800 + (buttonRect.w - textSurface->w) / 2, 10 + (buttonRect.h - textSurface->h) / 2, textSurface->w, textSurface->h};
    SDL_RenderCopy(m_renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    // Jouer le dé spécial
    SDL_SetRenderDrawColor(m_renderer, 173, 216, 230, 255); // Bleu clair
    buttonRect = {800, 100, 150, 50}; // Rectangle autour du texte "Jouer le dé spécial"
    SDL_RenderFillRect(m_renderer, &buttonRect);

    textSurface = TTF_RenderText_Solid(m_font, "Jouer le de special", {0, 0, 0, 255}); // Noir
    textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
    textRect = {800 + (buttonRect.w - textSurface->w) / 2, 100 + (buttonRect.h - textSurface->h) / 2, textSurface->w, textSurface->h};
    SDL_RenderCopy(m_renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    // Texte "Résultat du dé : "
    std::string resultat_str = std::to_string(resultat_de);
    if (resultat_de == -1) resultat_str = " ";
    textSurface = TTF_RenderText_Solid(m_font, resultat_str.c_str(), {0, 0, 0, 255}); // Noir
    textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
    textRect = {800 + buttonRect.w + 20, 10 + (buttonRect.h - textSurface->h) / 2, textSurface->w, textSurface->h};
    SDL_RenderCopy(m_renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    // Texte "Résultat du dé spécial : "
    std::string special_result;
    switch(resultat_de_special) {
        case 0:
            special_result = "rouge";
            break;
        case 1:
        case 2:
        case 3:
            special_result = "vert";
            break;
        case 4:
            special_result = "H (gratuit)";
            break;
        case 5:
            special_result = "2D (double)";
            break;
        default:
            special_result = " ";
    }
    textSurface = TTF_RenderText_Solid(m_font, special_result.c_str(), {0, 0, 0, 255}); // Noir
    textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
    textRect = {800 + buttonRect.w + 20, 100 + (buttonRect.h - textSurface->h) / 2, textSurface->w, textSurface->h};
    SDL_RenderCopy(m_renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    // Affichage de l'image en fonction du résultat du dé
    SDL_Rect imageRect = {325, 230, 120, 120}; // Position et taille de l'image
    SDL_Surface* diceSurface = nullptr;
    SDL_Texture* diceTexture = nullptr;

    switch (resultat_de) {
        case 1:
            diceSurface = IMG_Load("de1.png");
            break;
        case 2:
            diceSurface = IMG_Load("de2.png");
            break;
        case 3:
            diceSurface = IMG_Load("de3.png");
            break;
        case 4:
            diceSurface = IMG_Load("de4.png");
            break;
        case 5:
            diceSurface = IMG_Load("de5.png");
            break;
        case 6:
            diceSurface = IMG_Load("de6.png");
            break;
        default:
            diceSurface = IMG_Load("de_default1.png");
            break;
    }

    if (!diceSurface) {
        printf("Unable to load image! SDL_image Error: %s\n", IMG_GetError());
    } else {
        diceTexture = SDL_CreateTextureFromSurface(m_renderer, diceSurface);
        if (!diceTexture) {
            printf("Unable to create texture from image! SDL Error: %s\n", SDL_GetError());
        } else {
            SDL_SetTextureBlendMode(diceTexture, SDL_BLENDMODE_BLEND);
            SDL_RenderCopy(m_renderer, diceTexture, NULL, &imageRect);
            SDL_DestroyTexture(diceTexture);
        }
        SDL_FreeSurface(diceSurface);
    }
}

//------------------------------------------------------------------------------------------------------------//

void Renderer::renderTable(const Joueur& joueurs, const std::vector<int>& occupTerrain, std::vector<int> typeHotel) {
    // Charger les images
    SDL_Surface* houseSurface = IMG_Load("hotel_debase.png");
    if (!houseSurface) {
        printf("Unable to load image! SDL_image Error: %s\n", IMG_GetError());
        return; // Gérer l'erreur de chargement de l'image
    }
    SDL_Surface* houseSurface2 = IMG_Load("hotel_annexe_1.png");
    if (!houseSurface2) {
        printf("Unable to load image! SDL_image Error: %s\n", IMG_GetError());
        SDL_FreeSurface(houseSurface); // Libérer la première surface en cas d'erreur
        return; // Gérer l'erreur de chargement de l'image
    }

    // Réduire la taille des images si nécessaire
    int targetWidth = 40; // Largeur cible
    int targetHeight = 40; // Hauteur cible

    SDL_Surface* scaledSurface1 = SDL_CreateRGBSurfaceWithFormat(0, targetWidth, targetHeight, 32, houseSurface->format->format);
    SDL_BlitScaled(houseSurface, NULL, scaledSurface1, NULL);

    SDL_Surface* scaledSurface2 = SDL_CreateRGBSurfaceWithFormat(0, targetWidth, targetHeight, 32, houseSurface2->format->format);
    SDL_BlitScaled(houseSurface2, NULL, scaledSurface2, NULL);

    SDL_Texture* houseTexture = SDL_CreateTextureFromSurface(m_renderer, scaledSurface1);
    SDL_Texture* houseTexture2 = SDL_CreateTextureFromSurface(m_renderer, scaledSurface2);

    if (!houseTexture || !houseTexture2) {
        printf("Unable to create texture from image! SDL Error: %s\n", SDL_GetError());
        SDL_FreeSurface(scaledSurface1);
        SDL_FreeSurface(scaledSurface2);
        SDL_FreeSurface(houseSurface);
        SDL_FreeSurface(houseSurface2);
        return; // Gérer l'erreur de création de la texture
    }
    SDL_SetTextureBlendMode(houseTexture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(houseTexture2, SDL_BLENDMODE_BLEND);
    SDL_Rect imageRect1 = {10, 800, 40, 40}; // Rectangle pour la première position
    SDL_Rect imageRect2 = {10, 850, 40, 40}; // Rectangle pour la deuxième position
    SDL_RenderCopy(m_renderer, houseTexture, NULL, &imageRect1);
    SDL_RenderCopy(m_renderer, houseTexture2, NULL, &imageRect2);

    // Libérer la mémoire des surfaces originales et des surfaces réduites
    SDL_FreeSurface(scaledSurface1);
    SDL_FreeSurface(scaledSurface2);
    SDL_FreeSurface(houseSurface);
    SDL_FreeSurface(houseSurface2);
    
    // Tableau avec 3 lignes et 6 colonnes
    std::vector<std::vector<std::string>> tableContents = {
        {" ", "Argent", "Hotel1", "Hotel2", "Hotel3", "Hotel4"},
        {"Alicia", "", "", "", "", ""},
        {"Charbel", "", "", "", "", ""}
    };

    // Récupérer les montants d'argent des joueurs 1 et 2
    std::string argentJoueur1 = std::to_string(joueurs.getArgent(0)); // Joueur 1
    std::string argentJoueur2 = std::to_string(joueurs.getArgent(1)); // Joueur 2

    // Remplacer les cases correspondantes dans le tableau par les montants d'argent
    tableContents[1][1] = argentJoueur1; // Montant d'argent pour Joueur 1
    tableContents[2][1] = argentJoueur2; // Montant d'argent pour Joueur 2
    
    // Mise à jour du tableau tableContents pour afficher "X" si le terrain est occupé par joueur1 ou joueur2
    for (size_t i = 0; i < typeHotel.size(); ++i) {
        if (occupTerrain[i] == 0) { // Terrain occupé par Joueur 1
            tableContents[1][2 + i] = "X";
        } else if (occupTerrain[i] == 1) { // Terrain occupé par Joueur 2
            tableContents[2][2 + i] = "X";
        }
    }

    // Position initiale du tableau
    int tableX = 10;
    int tableY = 600;
    int cellWidth = 150;
    int cellHeight = 50;

    // Rendu du tableau
    for (int i = 0; i < tableContents.size(); ++i) {
        for (int j = 0; j < tableContents[i].size(); ++j) {
            // Calcul des coordonnées de la cellule
            int cellX = tableX + j * cellWidth;
            int cellY = tableY + i * cellHeight;

            // Rectangle pour la cellule
            SDL_Rect cellRect = {cellX, cellY, cellWidth, cellHeight};

            // Couleur de fond de la cellule
            SDL_SetRenderDrawColor(m_renderer, 192, 192, 192, 255); // Gris clair
            SDL_RenderFillRect(m_renderer, &cellRect);

            // Bordure de la cellule
            SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255); // Noir
            SDL_RenderDrawRect(m_renderer, &cellRect);

            // Texte à afficher dans la cellule
            std::string cellText = tableContents[i][j];
            SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, cellText.c_str(), {0, 0, 0, 255}); // Noir
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);

            // Position du texte au centre de la cellule
            int textWidth, textHeight;
            SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);
            SDL_Rect textRect = {cellX + (cellWidth - textWidth) / 2, cellY + (cellHeight - textHeight) / 2, textWidth, textHeight};

            // Rendu du texte
            SDL_RenderCopy(m_renderer, textTexture, NULL, &textRect);

            // Libération de la surface et de la texture du texte
            SDL_FreeSurface(textSurface);
            SDL_DestroyTexture(textTexture);
        }
    }

    // Affichage des images hotel
    for (size_t i = 0; i < typeHotel.size(); ++i) {
        if (typeHotel[i] == 0) { // Si l'hotel est acheté
            SDL_Rect imageRect;
            if (occupTerrain[i] == 0) { // Terrain occupé par Joueur 1
                imageRect = { static_cast<int>(tableX + (2 + i) * cellWidth + (cellWidth - targetWidth) / 2), static_cast<int>(tableY + cellHeight + (cellHeight - targetHeight) / 2),  targetWidth, targetHeight};
            } else if (occupTerrain[i] == 1) { // Terrain occupé par Joueur 2
                imageRect = {static_cast<int>(tableX + (2 + i) * cellWidth + (cellWidth - targetWidth) / 2), static_cast<int>(tableY + 2 * cellHeight + (cellHeight - targetHeight) / 2), targetWidth, targetHeight};
            }
            SDL_RenderCopy(m_renderer, houseTexture, NULL, &imageRect);
        }
    }
    // Affichage des images hotelannexe
    for (size_t i = 0; i < typeHotel.size(); ++i) {
        if (typeHotel[i] == 1) { // Si l'hotel annexe est acheté
            SDL_Rect imageRect;
            if (occupTerrain[i] == 0) { // Terrain occupé par Joueur 1
                imageRect = {static_cast<int>(tableX + (2 + i) * cellWidth + (cellWidth - targetWidth) / 2), tableY + cellHeight + (cellHeight - targetHeight) / 2, targetWidth, targetHeight};
            } else if (occupTerrain[i] == 1) { // Terrain occupé par Joueur 2
                imageRect = {static_cast<int>(tableX + (2 + i) * cellWidth + (cellWidth - targetWidth) / 2), tableY + 2 * cellHeight + (cellHeight - targetHeight) / 2, targetWidth, targetHeight};
            }
            SDL_RenderCopy(m_renderer, houseTexture2, NULL, &imageRect);
        }
    }

    // Libérer la mémoire de la texture
    SDL_DestroyTexture(houseTexture);
    // Libérer la mémoire de la texture
    SDL_DestroyTexture(houseTexture2);


    // Dessiner un carré rouge devant "Joueur 1"
    SDL_Rect redSquare = {40, 671, 10, 10};
    SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255); // Rouge
    SDL_RenderFillRect(m_renderer, &redSquare);

    // Dessiner un carré vert devant "Joueur 2"
    SDL_Rect blueSquare = {40, 721, 10, 10};
    SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255); // Vert
    SDL_RenderFillRect(m_renderer, &blueSquare);

    // Texte "X : Achat terrain"
    SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, "X : Achat terrain", {0, 0, 0, 255}); // Noir
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
    SDL_Rect textRect = {10, 780, textSurface->w, textSurface->h};
    SDL_RenderCopy(m_renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    // Texte " : 1 hotel"
    textSurface = TTF_RenderText_Solid(m_font, " : 1 hotel", {0, 0, 0, 255}); // Noir
    textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
    textRect = {50, 810, textSurface->w, textSurface->h};
    SDL_RenderCopy(m_renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    // Texte " : 2 hotels"
    textSurface = TTF_RenderText_Solid(m_font, " : 1 hotel de luxe", {0, 0, 0, 255}); // Noir
    textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
    textRect = {50, 860, textSurface->w, textSurface->h};
    SDL_RenderCopy(m_renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);


    // Achat terrain
    SDL_SetRenderDrawColor(m_renderer, 173, 216, 230, 255); // Bleu clair
    SDL_Rect buttonRect = {1250, 10, 150, 50}; // Rectangle 
    SDL_RenderFillRect(m_renderer, &buttonRect);

    textSurface = TTF_RenderText_Solid(m_font, "Achat terrain", {0, 0, 0, 255}); // Noir
    textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
    textRect = {1250 + (buttonRect.w - textSurface->w) / 2, 10 + (buttonRect.h - textSurface->h) / 2, textSurface->w, textSurface->h};
    SDL_RenderCopy(m_renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    
    // Achat hotel
    SDL_SetRenderDrawColor(m_renderer, 173, 216, 230, 255); // Bleu clair
    buttonRect = {1250, 100, 150, 50}; // Rectangle 
    SDL_RenderFillRect(m_renderer, &buttonRect);

    textSurface = TTF_RenderText_Solid(m_font, "Achat hotel(s)", {0, 0, 0, 255}); // Noir
    textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
    textRect = {1250 + (buttonRect.w - textSurface->w) / 2, 100 + (buttonRect.h - textSurface->h) / 2, textSurface->w, textSurface->h};
    SDL_RenderCopy(m_renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    
    // Achat entree
    SDL_SetRenderDrawColor(m_renderer, 173, 216, 230, 255); // Bleu clair
    buttonRect = {1250, 190, 150, 50}; // Rectangle 
    SDL_RenderFillRect(m_renderer, &buttonRect);

    textSurface = TTF_RenderText_Solid(m_font, "Achat entree(s)", {0, 0, 0, 255}); // Noir
    textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
    textRect = {1250 + (buttonRect.w - textSurface->w) / 2, 190 + (buttonRect.h - textSurface->h) / 2, textSurface->w, textSurface->h};
    SDL_RenderCopy(m_renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    // Oui/non
    textSurface = TTF_RenderText_Solid(m_font, "OUI / NON ", {0, 0, 0, 255}); // Noir
    textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
    textRect = {1250 + buttonRect.w + 20, 10 + (buttonRect.h - textSurface->h) / 2, textSurface->w, textSurface->h};
    SDL_Rect textRect2 = {1250 + buttonRect.w + 20, 100 + (buttonRect.h - textSurface->h) / 2, textSurface->w, textSurface->h};
    SDL_Rect textRect3 = {1250 + buttonRect.w + 20, 190 + (buttonRect.h - textSurface->h) / 2, textSurface->w, textSurface->h};
    
    SDL_RenderCopy(m_renderer, textTexture, NULL, &textRect);
    SDL_RenderCopy(m_renderer, textTexture, NULL, &textRect2);
    SDL_RenderCopy(m_renderer, textTexture, NULL, &textRect3);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

//------------------------------------------------------------------------------------------------------------//

void Renderer::renderCases() 
{
    Case cases = Case();
    // Afficher les informations de chaque case
    for (int i = 0; i < 30; ++i) {
        cases.display(m_renderer, m_font, i);
    }
}

//------------------------------------------------------------------------------------------------------------//

void Renderer::afficherPion(const Joueur& joueurs) const { 
    const Case& cases = Case();
    // Récupérer les positions des joueurs
    int positionJoueur1 = joueurs.getPosition(0) -1; //car les cases commencent à 1
    int positionJoueur2 = joueurs.getPosition(1) -1;



    // Dessiner le pion rouge pour le joueur 1
    SDL_Rect redPion = {cases.getX(positionJoueur1)+2, cases.getY(positionJoueur1)+2, 10, 10};
    if (positionJoueur1 == 0) redPion = {cases.getX(positionJoueur1) +15, cases.getY(positionJoueur1) +2, 10, 10};
    SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255); // Rouge
    SDL_RenderFillRect(m_renderer, &redPion);
     // Dessiner le pion vert pour le joueur 2
    SDL_Rect greenPion = {cases.getX(positionJoueur2)+2, cases.getY(positionJoueur2)+2, 10, 10};
    SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255); // Vert
    SDL_RenderFillRect(m_renderer, &greenPion);
}

//------------------------------------------------------------------------------------------------------------//

void Renderer::renderTerminal(const std::vector<std::string>& phrases) {
    // Couleur du texte : blanc
    SDL_Color textColor = {255, 255, 255};

    // Couleur du rectangle : noir
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);

    // Rectangle noir
    SDL_Rect rect = {800, 390, 600, 200};
    SDL_RenderFillRect(m_renderer, &rect);

    int yPos = 400; // Position verticale initiale pour le texte

    // Affichage du texte
    for (const auto& phrase : phrases) {
        // Rendu de la phrase actuelle
        SDL_Surface* surface = TTF_RenderText_Solid(m_font, phrase.c_str(), textColor);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
        SDL_Rect textRect = {810, yPos, 0, 0}; // Position du texte
        SDL_QueryTexture(texture, nullptr, nullptr, &textRect.w, &textRect.h);
        SDL_RenderCopy(m_renderer, texture, nullptr, &textRect);

        // Mise à jour de l'affichage
        SDL_RenderPresent(m_renderer);

        // Attendre un certain temps avant d'afficher la phrase suivante
        SDL_Delay(500); // Attendre 1 seconde entre chaque phrase

        // Mettre à jour la position verticale pour la prochaine phrase
        yPos += textRect.h + 10;

        // Libérer la mémoire
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
    SDL_Delay(1000);
}

//------------------------------------------------------------------------------------------------------------//

void Renderer::renderHotelAffiche(const std::vector<int>& typeHotel) {
    SDL_Rect imageRect;

    // Charger et afficher les images en fonction du type d'hôtel
    for(int index = 0; index < typeHotel.size(); index++) {
        int i = typeHotel[index];
        if(i != -1) {
            // Charger l'image appropriée en fonction du type d'hôtel
            SDL_Surface* houseSurface = nullptr;
            if(i == 0) {
                houseSurface = IMG_Load("hotel_debase.png");
                //printf("Affichage de l'hôtel de base\n");
            } else if(i == 1) {
                houseSurface = IMG_Load("hotel_annexe_1.png");
                //printf("Affichage de l'annexe d'hôtel\n");
            }

            // Vérifier si l'image a été chargée correctement
            if (!houseSurface) {
                printf("Unable to load image! SDL_image Error: %s\n", IMG_GetError());
                // Gérer l'erreur de chargement de l'image
            } else {
                // Réduire la taille de l'image si nécessaire
                int targetWidth = 100; // Largeur cible
                int targetHeight = 100; // Hauteur cible
                SDL_Surface* scaledSurface = SDL_CreateRGBSurfaceWithFormat(0, targetWidth, targetHeight, 32, houseSurface->format->format);
                SDL_BlitScaled(houseSurface, NULL, scaledSurface, NULL);

                // Créer une texture à partir de l'image réduite
                SDL_Texture* houseTexture = SDL_CreateTextureFromSurface(m_renderer, scaledSurface);
                if (!houseTexture) {
                    printf("Unable to create texture from image! SDL Error: %s\n", SDL_GetError());
                    // Gérer l'erreur de création de la texture
                } else {
                    // Configurer le mode de blending pour la transparence
                    SDL_SetTextureBlendMode(houseTexture, SDL_BLENDMODE_BLEND);

                    // Définir le rectangle de destination en fonction de l'index
                    switch (index) {
                        case 0:
                            imageRect = {20, 400, 100, 100}; // Rectangle pour la première position
                            break;
                        case 1:
                            imageRect = {20, 100, 100, 100}; // Rectangle pour la deuxième position
                            break;
                        case 2:
                            imageRect = {620, 100, 100, 100}; // Rectangle pour la troisième position
                            break;
                        case 3:
                            imageRect = {620, 470, 100, 100}; // Rectangle pour la quatrième position
                            break;
                    }

                    // Afficher l'image aux différentes positions
                    SDL_RenderCopy(m_renderer, houseTexture, NULL, &imageRect);

                    // Libérer la mémoire de la texture
                    SDL_DestroyTexture(houseTexture);
                }

                // Libérer la mémoire des surfaces
                SDL_FreeSurface(scaledSurface);
                SDL_FreeSurface(houseSurface);
            }
        }
    }
}

//------------------------------------------------------------------------------------------------------------//

void Renderer::renderBanqueAffiche() {
    SDL_Rect imageRect;

    // Charger l'image
    SDL_Surface* houseSurface = IMG_Load("banque.png");

    if (!houseSurface) {
        printf("Unable to load image! SDL_image Error: %s\n", IMG_GetError());
        // Gérer l'erreur de chargement de l'image
    } 
    else {
        // Activer la transparence si nécessaire (inutile pour PNG avec alpha, mais bon à savoir)
        SDL_SetColorKey(houseSurface, SDL_TRUE, SDL_MapRGB(houseSurface->format, 0, 0, 0));

        // Réduire la taille de l'image si nécessaire
        int targetWidth = 90; // Largeur cible
        int targetHeight = 90; // Hauteur cible
        SDL_Surface* scaledSurface = SDL_CreateRGBSurfaceWithFormat(0, targetWidth, targetHeight, 32, houseSurface->format->format);
        SDL_BlitScaled(houseSurface, NULL, scaledSurface, NULL);

        // Créer une texture à partir de l'image réduite
        SDL_Texture* houseTexture = SDL_CreateTextureFromSurface(m_renderer, scaledSurface);
        if (!houseTexture) {
            printf("Unable to create texture from image! SDL Error: %s\n", SDL_GetError());
            // Gérer l'erreur de création de la texture
        } 
        else {
            // Configurer le mode de blending pour la transparence
            SDL_SetTextureBlendMode(houseTexture, SDL_BLENDMODE_BLEND);
            
            imageRect = {330, 10, 90, 90}; // Rectangle pour la première position

            // Afficher l'image aux différentes positions
            SDL_RenderCopy(m_renderer, houseTexture, NULL, &imageRect);

            // Libérer la mémoire de la texture et de la surface
            SDL_DestroyTexture(houseTexture);
        }
        SDL_FreeSurface(scaledSurface);
        SDL_FreeSurface(houseSurface);            
    }
}

//------------------------------------------------------------------------------------------------------------//

void Renderer::renderMairieAffiche() {
    SDL_Rect imageRect;

    // Charger l'image
    SDL_Surface* houseSurface = IMG_Load("mairie.png");

    if (!houseSurface) {
        printf("Unable to load image! SDL_image Error: %s\n", IMG_GetError());
        // Gérer l'erreur de chargement de l'image
    } 
    else {
        // Activer la transparence si nécessaire
        SDL_SetColorKey(houseSurface, SDL_TRUE, SDL_MapRGB(houseSurface->format, 0, 0, 0));

        // Réduire la taille de l'image si nécessaire
        int targetWidth = 90; // Largeur cible
        int targetHeight = 90; // Hauteur cible
        SDL_Surface* scaledSurface = SDL_CreateRGBSurfaceWithFormat(0, targetWidth, targetHeight, 32, houseSurface->format->format);
        SDL_BlitScaled(houseSurface, NULL, scaledSurface, NULL);

        // Créer une texture à partir de l'image réduite
        SDL_Texture* houseTexture = SDL_CreateTextureFromSurface(m_renderer, scaledSurface);
        if (!houseTexture) {
            printf("Unable to create texture from image! SDL Error: %s\n", SDL_GetError());
            // Gérer l'erreur de création de la texture
        } 
        else {
            // Configurer le mode de blending pour la transparence
            SDL_SetTextureBlendMode(houseTexture, SDL_BLENDMODE_BLEND);
            
            imageRect = {330, 500, 90, 90}; // Rectangle pour la première position

            // Afficher l'image aux différentes positions
            SDL_RenderCopy(m_renderer, houseTexture, NULL, &imageRect);

            // Libérer la mémoire de la texture et de la surface
            SDL_DestroyTexture(houseTexture);
        }
        SDL_FreeSurface(scaledSurface);
        SDL_FreeSurface(houseSurface);            
    }
}

//------------------------------------------------------------------------------------------------------------//

void Renderer::renderEntreeAffiche(std::vector<int>& entrees){
    SDL_Rect imageRect;

    // Charger et afficher les images en fonction du type d'hôtel
    for(int index = 0; index < entrees.size(); index++) {
        int i = entrees[index];
        if(i != -1) {
            // Charger l'image appropriée en fonction du type d'hôtel
            SDL_Surface* houseSurface = nullptr;
            if(i == 0) {
                houseSurface = IMG_Load("entrance.png");
                //printf("Affichage de l'hôtel de base\n");
            } else if(i == 1) {
                houseSurface = IMG_Load("hotel_annexe_1.png"); //rien pour l'instant
                //printf("Affichage de l'annexe d'hôtel\n");
            }

            // Vérifier si l'image a été chargée correctement
            if (!houseSurface) {
                printf("Unable to load image! SDL_image Error: %s\n", IMG_GetError());
                // Gérer l'erreur de chargement de l'image
            } else {
                // Réduire la taille de l'image si nécessaire
                int targetWidth = 80; // Largeur cible
                int targetHeight = 80; // Hauteur cible
                SDL_Surface* scaledSurface = SDL_CreateRGBSurfaceWithFormat(0, targetWidth, targetHeight, 32, houseSurface->format->format);
                SDL_BlitScaled(houseSurface, NULL, scaledSurface, NULL);

                // Créer une texture à partir de l'image réduite
                SDL_Texture* houseTexture = SDL_CreateTextureFromSurface(m_renderer, scaledSurface);
                if (!houseTexture) {
                    printf("Unable to create texture from image! SDL Error: %s\n", SDL_GetError());
                    // Gérer l'erreur de création de la texture
                } else {
                    // Configurer le mode de blending pour la transparence
                    SDL_SetTextureBlendMode(houseTexture, SDL_BLENDMODE_BLEND);

                    // Définir le rectangle de destination en fonction de l'index
                    switch (index) {
                        case 0:
                            imageRect = {200, 350, targetWidth, targetHeight}; // Rectangle pour la première position
                            break;
                        case 1:
                            imageRect = {200, 150, targetWidth, targetHeight}; // Rectangle pour la deuxième position
                            break;
                        case 2:
                            imageRect = {450, 150, targetWidth, targetHeight}; // Rectangle pour la troisième position
                            break;
                        case 3:
                            imageRect = {450, 350, targetWidth, targetHeight}; // Rectangle pour la quatrième position
                            break;
                    }

                    // Afficher l'image aux différentes positions
                    SDL_RenderCopy(m_renderer, houseTexture, NULL, &imageRect);

                    // Libérer la mémoire de la texture
                    SDL_DestroyTexture(houseTexture);
                }

                // Libérer la mémoire des surfaces
                SDL_FreeSurface(scaledSurface);
                SDL_FreeSurface(houseSurface);
            }
        }
    }
}

