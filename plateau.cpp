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

void Renderer::renderGame(const Joueur& joueurs, const std::vector<std::string>& phrases, int resultat_de, int resultat_de_special, const std::vector<int>& typeHotel) {
    // Effacer l'écran
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_renderer);
    
    // Rendu du circuit
    renderTrack();

    // Rendu des hôtels
    renderHotels();
    renderHotelAffiche(typeHotel);
    // Rendu dés
    renderDe(resultat_de, resultat_de_special);

    // Rendu du tableau
    renderTable();
    
    // Rendu des cases
    renderCases();

    // Rendu pions
    afficherPion(joueurs);

    // Rendu terminal
    renderTerminal(phrases);

    // Rendu hotels
    renderHotelAffiche(typeHotel);

    // Mettre à jour l'affichage
    SDL_RenderPresent(m_renderer);

}

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
    buttonRect = {800, 100, 150, 50}; // Rectangle autour du texte "Jouer le dé"
    SDL_RenderFillRect(m_renderer, &buttonRect);

    textSurface = TTF_RenderText_Solid(m_font, "Jouer le de special", {0, 0, 0, 255}); // Noir
    textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
    textRect = {800 + (buttonRect.w - textSurface->w) / 2, 100 + (buttonRect.h - textSurface->h) / 2, textSurface->w, textSurface->h};
    SDL_RenderCopy(m_renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    /*****************CLIC SOURIS**************/
    // Texte "Résultat du dé : "
    std::string resultat_str = std::to_string(resultat_de);
    textSurface = TTF_RenderText_Solid(m_font, resultat_str.c_str(), {0, 0, 0, 255}); // Noir
    if (resultat_de == -1)textSurface = TTF_RenderText_Solid(m_font, " ", {0, 0, 0, 255}); // Noir
    textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
    textRect = {800 + buttonRect.w + 20, 10 + (buttonRect.h - textSurface->h) / 2, textSurface->w, textSurface->h};
    SDL_RenderCopy(m_renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);


    // Texte "Résultat du dé special : "
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
}

void Renderer::renderTable() {
    // Tableau avec 3 lignes et 6 colonnes
    // Définition des textes à afficher dans chaque cellule
    std::vector<std::vector<std::string>> tableContents = {
        {" ", "Argent", "Hotel1", "Hotel2", "Hotel3", "Hotel4"},
        {"Joueur 1", "", "", "", "", ""},
        {"Joueur 2", "", "", "", "", ""}
    };

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

    // Charger l'image
    SDL_Surface* houseSurface = IMG_Load("image_maison.png");
    if (!houseSurface) {
        printf("Unable to load image! SDL_image Error: %s\n", IMG_GetError());
        // Gérer l'erreur de chargement de l'image
    } else {
        // Réduire la taille de l'image si nécessaire
        int targetWidth = 40; // Largeur cible
        int targetHeight = 40; // Hauteur cible
        SDL_Surface* scaledSurface = SDL_CreateRGBSurface(0, targetWidth, targetHeight, 32, 0, 0, 0, 0);
        SDL_BlitScaled(houseSurface, NULL, scaledSurface, NULL);

        // Créer une texture à partir de l'image réduite
        SDL_Texture* houseTexture = SDL_CreateTextureFromSurface(m_renderer, scaledSurface);
        if (!houseTexture) {
            printf("Unable to create texture from image! SDL Error: %s\n", SDL_GetError());
            // Gérer l'erreur de création de la texture
        } else {
            // Définir la destination et le rendu de l'image réduite
            // Définir les rectangles pour les positions de l'image
            SDL_Rect imageRect1 = {10, 800, 40, 40}; // Rectangle pour la première position
            SDL_Rect imageRect2 = {10, 850, 40, 40}; // Rectangle pour la deuxième position
            SDL_Rect imageRect3 = {50, 850, 40, 40}; // Rectangle pour la troisième position

            // Afficher l'image aux différentes positions
            SDL_RenderCopy(m_renderer, houseTexture, NULL, &imageRect1);
            SDL_RenderCopy(m_renderer, houseTexture, NULL, &imageRect2);
            SDL_RenderCopy(m_renderer, houseTexture, NULL, &imageRect3);
            // Libérer la mémoire de la texture et de la surface
            SDL_DestroyTexture(houseTexture);
        }

        // Libérer la mémoire de la surface originale et de la surface réduite
        SDL_FreeSurface(scaledSurface);
        SDL_FreeSurface(houseSurface);
    }


    // Texte " : 1 hotel"
    textSurface = TTF_RenderText_Solid(m_font, " : 1 hotel", {0, 0, 0, 255}); // Noir
    textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
    textRect = {50, 810, textSurface->w, textSurface->h};
    SDL_RenderCopy(m_renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    // Texte " : 2 hotels"
    textSurface = TTF_RenderText_Solid(m_font, " : 2 hotels", {0, 0, 0, 255}); // Noir
    textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
    textRect = {90, 860, textSurface->w, textSurface->h};
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


void Renderer::renderCases() 
{
    Case cases = Case();
    // Afficher les informations de chaque case
    for (int i = 0; i < 30; ++i) {
        cases.display(m_renderer, m_font, i);
    }
}


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

void Renderer::renderHotelAffiche(const std::vector<int>& typeHotel){
    SDL_Rect imageRect;
    // Charger l'image
    for(int index = 0; index < typeHotel.size(); index++){
        
        int i = typeHotel[index];
        if(i == 0 || i == 1){
            SDL_Surface* houseSurface = IMG_Load("hotel_debase.png");
            //std::cout << "on va construire hotel_debase.png sur terrain " << index << std::endl;
            if (!houseSurface) {
                printf("Unable to load image! SDL_image Error: %s\n", IMG_GetError());
                // Gérer l'erreur de chargement de l'image
            } 
            else {
                // Réduire la taille de l'image si nécessaire
                int targetWidth = 100; // Largeur cible
                int targetHeight = 100; // Hauteur cible
                SDL_Surface* scaledSurface = SDL_CreateRGBSurface(0, targetWidth, targetHeight, 32, 0, 0, 0, 0);
                SDL_BlitScaled(houseSurface, NULL, scaledSurface, NULL);

                // Créer une texture à partir de l'image réduite
                SDL_Texture* houseTexture = SDL_CreateTextureFromSurface(m_renderer, scaledSurface);
                if (!houseTexture) {
                    printf("Unable to create texture from image! SDL Error: %s\n", SDL_GetError());
                    // Gérer l'erreur de création de la texture
                } 
                else {
                    switch (index) {
                        case 0:
                            if(i == 0){
                                imageRect = {20, 470, 100, 100}; // Rectangle pour la première position
                                break;
                            }
                        case 1:
                            if(i == 0){
                                imageRect = {20, 100, 100, 100}; // Rectangle pour la deuxième position
                                break;
                            }
                        case 2:
                            if(i == 0){
                                imageRect = {620, 100, 70, 90}; // Rectangle pour la deuxième position
                                break;
                            }
                        case 3:
                            if(i == 0){
                                imageRect = {620, 470, 70, 90}; // Rectangle pour la deuxième position
                                break;
                            }
                    } 
                }     
                    // Afficher l'image aux différentes positions
                    SDL_RenderCopy(m_renderer, houseTexture, NULL, &imageRect);
                    // Libérer la mémoire de la texture et de la surface
                    SDL_DestroyTexture(houseTexture);
                    SDL_FreeSurface(scaledSurface);
                    SDL_FreeSurface(houseSurface);
            
                // else if (typeHotel[i] == 1) {
                //             // Si le type d'hôtel est 1 (autre type d'hôtel), afficher l'hôtel correspondant sur le terrain i
                //             // Positionner l'image de l'hôtel en fonction de l'indice i
                //         }
                // Libérer la mémoire de la surface originale et de la surface réduite
            
            }
        }
    }
}


/*
void Renderer::renderHotelAffiche(int index)
{
    // Charger l'image
    if(index == -1){
        return;
    }
    else{
        SDL_Surface* houseSurface = IMG_Load("hotel_debase.png");
        std::cout << "on va construire hotel_debase.png sur terrain " << index << std::endl;
        if (!houseSurface) {
            printf("Unable to load image! SDL_image Error: %s\n", IMG_GetError());
            // Gérer l'erreur de chargement de l'image
        } else {
            // Réduire la taille de l'image si nécessaire
            int targetWidth = 40; // Largeur cible
            int targetHeight = 40; // Hauteur cible
            SDL_Surface* scaledSurface = SDL_CreateRGBSurface(0, targetWidth, targetHeight, 32, 0, 0, 0, 0);
            SDL_BlitScaled(houseSurface, NULL, scaledSurface, NULL);

            // Créer une texture à partir de l'image réduite
            SDL_Texture* houseTexture = SDL_CreateTextureFromSurface(m_renderer, scaledSurface);
            if (!houseTexture) {
                printf("Unable to create texture from image! SDL Error: %s\n", SDL_GetError());
                // Gérer l'erreur de création de la texture
            } else {
                SDL_Rect imageRect; // Rectangle pour la position de l'image

                // Utiliser un switch pour déterminer la position en fonction de index
                switch (index) {
                    case 0:
                        imageRect = {50, 500, 70, 90}; // Rectangle pour la première position
                        break;
                    case 1:
                        imageRect = {100, 300, 70, 90}; // Rectangle pour la deuxième position
                        break;
                    case 2:
                        imageRect = {100, 300, 70, 90}; // Rectangle pour la deuxième position
                        break;
                    case 3:
                        imageRect = {100, 300, 70, 90}; // Rectangle pour la deuxième position
                        break;
                }        
                // Afficher l'image aux différentes positions
                SDL_RenderCopy(m_renderer, houseTexture, NULL, &imageRect);
                // Libérer la mémoire de la texture et de la surface
                SDL_DestroyTexture(houseTexture);
            }

            // Libérer la mémoire de la surface originale et de la surface réduite
            SDL_FreeSurface(scaledSurface);
            SDL_FreeSurface(houseSurface);
        }
    }
}*/


