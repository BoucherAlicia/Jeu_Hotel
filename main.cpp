<<<<<<< HEAD
// main.cpp
#include <SDL2/SDL.h>
#include "plateau.hpp"
#include "terrain.hpp"
#include "joueur.hpp"
#include "case.hpp"
=======
#include "plateau.hpp"
#include "hotels.hpp"
#include "terrain.hpp"
void jouerPartie(SDL_Renderer* renderer, Renderer& gameRenderer) {
    // Création des joueurs
    std::vector<std::string> nomsJoueurs = {"Alicia", "Charbel"};
    std::vector<int> argentsInitiaux = {5000, 5000};
    std::vector<int> positionsInitiales = {1, 1};
    Joueur joueurs(nomsJoueurs, argentsInitiaux, positionsInitiales);
    int resultatDe = 0;
    int resultatDe_special = -1;
>>>>>>> c0631ad2d1e1bb3b46e8adad67a9369d949a867a

    // Création du dé normal
    DeNormal deNormal;
    DeSpecial deSpecial;

    // Déroulement du jeu pour n tours
    for (int tour = 1; tour <= 10; ++tour) {
        std::vector<std::string> tourPhrases = {
            "********************************************",
            "Tour " + std::to_string(tour),
            "********************************************"
        };

        for (int i = 0; i < nomsJoueurs.size(); ++i) {
            std::vector<std::string> joueurPhrases = {
                "C'est le tour du joueur " + std::to_string(i+1) + " - " + joueurs.getNom(i),
                "Le joueur " + joueurs.getNom(i) + " est a la case " + std::to_string(joueurs.getPosition(i)),
                "Veuillez lancer le de : "
            };
            std::vector<std::string> totalPhrases;
            totalPhrases.insert(totalPhrases.end(), tourPhrases.begin(), tourPhrases.end());
            totalPhrases.insert(totalPhrases.end(), joueurPhrases.begin(), joueurPhrases.end());
            gameRenderer.renderGame(joueurs, totalPhrases, resultatDe, resultatDe_special);
            // Attendre que le joueur lance le dé en cliquant sur le plateau
            bool deLance = false;
            while (!deLance) {
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
                        if (mouseX >= 800 && mouseX <= 950 && mouseY >= 100 && mouseY <= 150) {
                            // Clic détecté dans la zone "Jouer le dé spécial", donc lancer le dé spécial
                            resultatDe_special = deSpecial.lanceDe();
                        }
                        else if (mouseX >= 800 && mouseX <= 950 && mouseY >= 10 && mouseY <= 60) {
                            // Clic détecté dans la zone "Jouer le dé", donc lancer le dé
                            resultatDe = deNormal.lanceDe();
                            std::vector<std::string> dePhrases = {
                                "Le joueur avance de " + std::to_string(resultatDe) + " cases."
                            };
                            
                            // Mettre à jour la position du joueur
                            joueurs.setPosition(i, resultatDe);
                            std::vector<std::string> positionPhrases = {
                                "Le joueur est a maintenant a la case " + std::to_string(joueurs.getPosition(i))
                            };

                            if (joueurs.getPosition(i) != joueurs.getPosition((i + 1) % 2)) {
                                // Les joueurs ne sont pas sur la même case
                                std::vector<std::string> totalPhrases2;
                                totalPhrases2.insert(totalPhrases2.end(), tourPhrases.begin(), tourPhrases.end());
                                totalPhrases2.insert(totalPhrases2.end(), dePhrases.begin(), dePhrases.end());
                                totalPhrases2.insert(totalPhrases2.end(), positionPhrases.begin(), positionPhrases.end());
                                gameRenderer.renderGame(joueurs, totalPhrases2, resultatDe, resultatDe_special);
                            } else {
                                // Les joueurs sont sur la même case
                                // Mettre à jour la position du joueur
                                joueurs.setPosition(i, 1);
                                std::vector<std::string> memeCasePhrases = {
                                    "Le joueur se retrouve sur la meme case qu'un autre joueur.",
                                    "Il avance donc d'une case supplementaire.",
                                    "Le joueur est a maintenant a la case " + std::to_string(joueurs.getPosition(i))
                                };
                                std::vector<std::string> totalPhrases3;
                                totalPhrases3.insert(totalPhrases3.end(), tourPhrases.begin(), tourPhrases.end());
                                totalPhrases3.insert(totalPhrases3.end(), dePhrases.begin(), dePhrases.end());
                                totalPhrases3.insert(totalPhrases3.end(), positionPhrases.begin(), positionPhrases.end());
                                totalPhrases3.insert(totalPhrases3.end(), memeCasePhrases.begin(), memeCasePhrases.end());
                                gameRenderer.renderGame(joueurs, totalPhrases3, resultatDe, resultatDe_special);
                                SDL_Delay(500);
                            }
                            //Relancer le dé s'il était égal à 6
                            if (resultatDe == 6) 
                            {
                                // Afficher un message pour indiquer que le joueur relance le dé
                                std::vector<std::string> relancePhrases = {
                                    "Vous avez obtenu un 6, vous devez relancer le de : "
                                };
                                gameRenderer.renderGame(joueurs, relancePhrases, resultatDe, resultatDe_special);
                                SDL_Delay(1000); // Attendre un court instant avant de relancer le dé
                            } else {
                                // Marquer que le dé a été lancé
                                deLance = true;
                            }
                        }
                    }
                }
            }

        }
    }

    // Fin de la partie après n tours
    std::vector<std::string> finPartiePhrases = {
        "Fin de la partie"
    };
    gameRenderer.renderGame(joueurs, finPartiePhrases, resultatDe, resultatDe_special);
    SDL_Delay(3000); // Attendre 3 secondes avant de fermer la fenêtre
}

int main() {
<<<<<<< HEAD
    int argentInitial = 25000;
    // Création des joueurs
    Joueur joueur1("Joueur 1", argentInitial);
    Joueur joueur2("Joueur 2", argentInitial);
/*---------------------------------------------------------------------------------------------------------------------*/
=======
>>>>>>> c0631ad2d1e1bb3b46e8adad67a9369d949a867a
    //Tests terrain.cpp
    Terrain terrain;
    int numerocase = 1;
    terrain.getTerrainAdjacent(numerocase);
    terrain.occupe(numerocase);
    terrain.getTerrainAdjacent(numerocase);
    numerocase = 7;
    terrain.getTerrainAdjacent(numerocase);
/*---------------------------------------------------------------------------------------------------------------------*/
<<<<<<< HEAD
=======
 

>>>>>>> c0631ad2d1e1bb3b46e8adad67a9369d949a867a
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
