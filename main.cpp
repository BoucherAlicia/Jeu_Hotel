#include "plateau.hpp"
#include "hotels.hpp"

void jouerPartie(SDL_Renderer* renderer, Renderer gameRenderer) {
    // Création des joueurs
    std::vector<std::string> nomsJoueurs = {"Alicia", "Charbel"};
    std::vector<int> argentsInitiaux = {5000, 5000};
    std::vector<int> positionsInitiales = {1, 1};
    Joueur joueurs(nomsJoueurs, argentsInitiaux, positionsInitiales);

    // Création du dé normal
    DeNormal deNormal;

    // Déroulement du jeu pour n tours
    for (int tour = 1; tour <= 10; ++tour) {
        std::cout << "********************************************" << std::endl << "Tour " << tour << std::endl;
        for (int i = 0; i < nomsJoueurs.size(); ++i) {
            std::cout << "********************************************" << std::endl << "C'est le tour du joueur " << i+1 << " - " << joueurs.getNom(i) << std::endl;
            
            // Afficher la position du joueur
            std::cout << "Le joueur " << joueurs.getNom(i) << " est à la case " << joueurs.getPosition(i) << std::endl;
            
            // Attendre que le joueur lance le dé en cliquant sur le plateau
            bool deLance = false;
            while (!deLance) {
                // Render the game
                gameRenderer.renderGame(joueurs);

                // Gestion des événements
                SDL_Event event;
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        // Quitter si l'utilisateur ferme la fenêtre
                        return;
                    }
                    // Vérifier si le clic de la souris se produit dans la zone "Jouer le dé"
                    if (event.type == SDL_MOUSEBUTTONDOWN) {
                        int mouseX, mouseY;
                        SDL_GetMouseState(&mouseX, &mouseY);
                        if (mouseX >= 800 && mouseX <= 950 && mouseY >= 10 && mouseY <= 60) {
                            // Clic détecté dans la zone "Jouer le dé", donc lancer le dé
                            int resultatDe = deNormal.lanceDe();
                            std::cout << "Le joueur avance de " << resultatDe << " cases." << std::endl;
                            
                            // Mettre à jour la position du joueur
                            joueurs.setPosition(i, resultatDe);
                            if (joueurs.getPosition(i) != joueurs.getPosition((i + 1) % 2)) {
                                // Les joueurs ne sont pas sur la même case
                            } else {
                                // Les joueurs sont sur la même case
                                std::cout << "Le joueur se retrouve sur la même case qu'un autre joueur. Il avance donc d'une case supplémentaire." << std::endl;
                                // Mettre à jour la position du joueur
                                joueurs.setPosition(i, 1);
                            }

                            // Marquer que le dé a été lancé
                            deLance = true;
                        }
                    }
                }
            }
        }
    }

    // Fin de la partie après n tours
    std::cout << "Fin de la partie" << std::endl;
    SDL_Delay(3000); // Attendre 3 secondes avant de fermer la fenêtre
}

int main() {
    Case cases = Case();

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
