#include "joueur.hpp"
#include "de_special.hpp"
#include <iostream>
#include "terrain.hpp"
#include "plateau.hpp"
void jouerPartie(SDL_Renderer* renderer, Renderer& gameRenderer) {
    // Création des joueurs
    Terrain terrain;
    std::vector<std::string> nomsJoueurs = {"Alicia", "Charbel"};
    std::vector<int> argentsInitiaux = {5000, 5000};
    std::vector<int> positionsInitiales = {1, 1};
    Joueur joueurs(nomsJoueurs, argentsInitiaux, positionsInitiales);
    int resultatDe = 0;
    int resultatDe_special = -1;

    // Création du dé normal
    DeNormal deNormal;
    DeSpecial deSpecial;
    std::vector<bool> tableauBool(4);
    std::vector<int> prixLoyer = {100, 200, 300, 400};

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
                            //----------------------------------------------------------------------------------------------------------------------------------------------//                            
                            std::string reponse;
                            bool estOccupe = false;
                            int numerocase = joueurs.getPosition(i);
                            std::cout << "position joueur : " << numerocase << std::endl;
                            const Terrain* terrainAdjacent = terrain.getTerrainAdjacent(numerocase);
                            int index = terrain.getTerrainIndex(numerocase);
                            std::cout << "index : " << index << std::endl;
                            if (terrainAdjacent != nullptr) {
                                // Utilisez le pointeur retourné pour accéder à m_estOccupe
                                estOccupe = terrainAdjacent->estOccupe();
                                std::cout << "position joueurrr : " << joueurs.getPosition(i) << std::endl;
                                if (tableauBool[index] == false) {
                                    //std::cout << (estOccupe ? "Oui" : "Non") << std::endl;
                                    std::cout << "Le terrain est libre, souhaitez vous l'acheter? (oui/non)" << std::endl;
                                    std::cin >> reponse;
                                    if (reponse == "oui") {
                                        //joueurs.retirerArgent(i, terrain.getPrix(numerocase));
                                        terrain.occupe(numerocase);
                                        tableauBool[index] = true;
                                        std::cout << "Vous avez achete le terrain" << std::endl;
                                        //std::cout << "Vous avez maintenant " << joueurs.getArgent(i) << " euros" << std::endl;
                                        std::cout << "est ce que vous voulez construire un hotel? (oui/non)" << std::endl;
                                        std::cin >> reponse;
                                        if (reponse == "oui") {
                                            //joueurs.retirerArgent(i, 1000);
                                            terrain.construit(numerocase);
                                            std::cout << "Vous avez construit un hotel" << std::endl;
                                            //std::cout << "Vous avez maintenant " << joueurs.getArgent(i) << " euros" << std::endl;
                                        }
                                    }
                                }
                                else {
                                    std::cout << "Le terrain est deja occupe" << std::endl;
                                    std::cout << "vous devez payer le loyer de " << prixLoyer[index] << "€" << std::endl;
                                    //std::cout << "il vous reste " << joueurs.getArgent(i) << "€" << std::endl;
                                }
                            }
                            else {
                                std::cerr << "Erreur : Terrain adjacent invalide." << std::endl;
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
