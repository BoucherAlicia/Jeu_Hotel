// jeu.cpp
#include "joueur.hpp"
#include "de_special.hpp"
#include <iostream>
#include "terrain.hpp"
#include "plateau.hpp"
#include "hotel.hpp"

void acheterHotel(Joueur& joueurs, std::vector<int>& typeHotel, Hotel& hotel, Terrain& terrain, int i, int index, int numerocase, Renderer& gameRenderer, std::vector<int>& entrees)
{
    std::string reponse;
    DeSpecial deSpecial;
    std::vector<std::string> phrases; // Tableau pour stocker les phrases à afficher
    if (joueurs.getArgent(i) >= 1000 && ((typeHotel[index] == -1) || (typeHotel[index] == 0))) {
        phrases = {"Est-ce que vous voulez construire un hotel pour 1000 euros ? (oui/non)"};
        gameRenderer.renderGame(joueurs, phrases, 0, -1, typeHotel, entrees);
        bool choixFait = false;
        while (!choixFait) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);

                    // Vérifiez si le clic est dans la zone du bouton "oui"
                    if (mouseX >= 1420 && mouseX <= 1450 && mouseY >= 100 && mouseY <= 160) {
                        reponse = "oui";
                        choixFait = true;
                    }
                    // Vérifiez si le clic est dans la zone du bouton "non"
                    else if (mouseX >= 1450 && mouseX <= 1480 && mouseY >= 100 && mouseY <= 160) {
                        reponse = "non";
                        choixFait = true;
                    }
                }
            }
        }
        if (reponse == "oui") {
            phrases = {"Vous voulez acheter un hotel.", "Vous devez lancer le de special :"};
            gameRenderer.renderGame(joueurs, phrases, 0, -1, typeHotel, entrees);
            int resultatDe_special = -1; // Initialize with an invalid value
            while (resultatDe_special == -1) {
                SDL_Event event;
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        // Quitter si l'utilisateur ferme la fenêtre
                        return;
                    } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                        int mouseX, mouseY;
                        SDL_GetMouseState(&mouseX, &mouseY);

                        // Vérifiez si le clic est dans la zone du bouton "de special"
                        if (mouseX >= 800 && mouseX <= 950 && mouseY >= 100 && mouseY <= 150) {
                            // Clic détecté dans la zone "Jouer le dé spécial", donc lancer le dé spécial
                            resultatDe_special = deSpecial.lanceDe();
                            gameRenderer.renderGame(joueurs, phrases, 0, resultatDe_special, typeHotel, entrees);
                            
                            std::vector<std::string> phrases2;
                            std::vector<std::string> totalPhrases;
                            
                            switch (resultatDe_special) {
                                case 0: // Rouge
                                    phrases2 = {
                                        "Le de est rouge, vous ne pouvez pas acheter d'hotel.",
                                        "Dommage pour vous, retentez votre chance une prochaine fois...",
                                    };
                                    totalPhrases.insert(totalPhrases.end(), phrases.begin(), phrases.end());
                                    totalPhrases.insert(totalPhrases.end(), phrases2.begin(), phrases2.end());
                                    gameRenderer.renderGame(joueurs, totalPhrases, 0, resultatDe_special, typeHotel, entrees);
                                    break;
                                
                                case 1: // Vert
                                case 2:
                                case 3:
                                    joueurs.retirerArgent(i, 1000);
                                    if (typeHotel[index] == -1) {
                                        typeHotel[index] = 0;
                                    } else {
                                        typeHotel[index] = 1;
                                    }
                                    hotel.construireHotel(index);
                                    terrain.construit(numerocase);
                                    phrases2 = {
                                        "Le de est vert, vous pouvez acheter l'hotel a 1000 euros.",
                                        "Vous avez construit un hotel",
                                        "Vous avez maintenant " + std::to_string(joueurs.getArgent(i)) + " euros"
                                    };
                                    totalPhrases.insert(totalPhrases.end(), phrases.begin(), phrases.end());
                                    totalPhrases.insert(totalPhrases.end(), phrases2.begin(), phrases2.end());
                                    gameRenderer.renderGame(joueurs, totalPhrases, 0, resultatDe_special, typeHotel, entrees);
                                    break;
                                
                                case 4: // Gratuit
                                    if (typeHotel[index] == -1) {
                                        typeHotel[index] = 0;
                                    } else {
                                        typeHotel[index] = 1;
                                    }
                                    hotel.construireHotel(index);
                                    terrain.construit(numerocase);
                                    phrases2 = {
                                        "Le de est H (gratuit), vous avez l'hotel gratuitement !",
                                        "Vous avez construit un hotel",
                                        "Vous avez toujours " + std::to_string(joueurs.getArgent(i)) + " euros"
                                    };
                                    totalPhrases.insert(totalPhrases.end(), phrases.begin(), phrases.end());
                                    totalPhrases.insert(totalPhrases.end(), phrases2.begin(), phrases2.end());
                                    gameRenderer.renderGame(joueurs, totalPhrases, 0, resultatDe_special, typeHotel, entrees);
                                    break;
                                
                                case 5: // Double
                                    joueurs.retirerArgent(i, 2000);
                                    if (typeHotel[index] == -1) {
                                        typeHotel[index] = 0;
                                    } else {
                                        typeHotel[index] = 1;
                                    }
                                    hotel.construireHotel(index);
                                    terrain.construit(numerocase);
                                    phrases2 = {
                                        "Le de est 2D (double), vous devez payer 2000 euros pour acheter l'hotel.",
                                        "Vous avez construit un hotel",
                                        "Vous avez maintenant " + std::to_string(joueurs.getArgent(i)) + " euros"
                                    };
                                    totalPhrases.insert(totalPhrases.end(), phrases.begin(), phrases.end());
                                    totalPhrases.insert(totalPhrases.end(), phrases2.begin(), phrases2.end());
                                    gameRenderer.renderGame(joueurs, totalPhrases, 0, resultatDe_special, typeHotel, entrees);
                                    break;
                                
                                default:
                                    phrases2 = {
                                        "Vous n'avez pas lance le de.",
                                    };
                                    totalPhrases.insert(totalPhrases.end(), phrases.begin(), phrases.end());
                                    totalPhrases.insert(totalPhrases.end(), phrases2.begin(), phrases2.end());
                                    gameRenderer.renderGame(joueurs, totalPhrases, 0, resultatDe_special, typeHotel, entrees);
                            }
                        }
                    }
                }
            }
        }
    } else {
        phrases = {"Vous avez decide de ne pas construire d'hotel."};
        gameRenderer.renderGame(joueurs, phrases, 0, -1, typeHotel, entrees);
    }
}

void passerParBanque(Joueur& joueurs, int joueurIndex, int anciennePosition, int nouvellePosition,std::vector<int>& typeHotel, Renderer& gameRenderer, std::vector<int>& entrees) {
    int caseBanque = 12;
    int nombreCases = 30; // Supposons que le plateau a 40 cases, modifiez ceci selon votre jeu.

    // Vérifiez si le joueur est passé par la case 12
    if ((anciennePosition < caseBanque && nouvellePosition >= caseBanque)) {
        joueurs.ajouterArgent(joueurIndex, 1000);
        std::vector<std::string> phrasesTerrain2 = { joueurs.getNom(joueurIndex) + " passe par la banque et gagne 1000 euros !!!!" };
        gameRenderer.renderGame(joueurs, phrasesTerrain2, 0, -1, typeHotel, entrees);
    }
}

void acheterEntreesHotels(Joueur& joueurs, int joueurIndex, int anciennePosition, int nouvellePosition, std::vector<int>& typeHotel, Renderer& gameRenderer, std::vector<int>& entrees, std::vector<bool> tableauBool, std::vector<int> occupTerrain) {
    int caseDebut = 27;
    int caseFin = 30;
    std::string reponse;
    std::vector<std::string> phrases1;
    // Vérifier si le joueur est entre les cases 27 et 30
    if(anciennePosition >= caseDebut && anciennePosition <= caseFin){
        phrases1 = {"Vous n'avez plus le droit d'acheter des entrees pour ce tour."};
        gameRenderer.renderGame(joueurs, phrases1, 0, -1, typeHotel, entrees);
    }
    else if (nouvellePosition >= caseDebut && nouvellePosition <= caseFin) {
        phrases1 = {"Vous etes entre les cases 27 et 30. Voulez vous acheter des entrées pour les hotels que vous occupez ? (oui/non)"};
        gameRenderer.renderGame(joueurs, phrases1, 0, -1, typeHotel, entrees);
        for(int i = 0; i < tableauBool.size(); i++) {
            if ((tableauBool[i] == true) && (occupTerrain[i] == joueurIndex)) {
                int show = i + 1;
                std::vector<std::string> phrases2 = {"Vous etes elligible pour acheter des entrees pour les hotels que vous occupez.", 
                "Voulez-vous acheter des entrees pour l'hotel " + std::to_string(show) + " ? (oui/non)"}; 
                
                bool choixFait = false;
                while (!choixFait) {
                    SDL_Event event;
                    while (SDL_PollEvent(&event)) {
                        if (event.type == SDL_MOUSEBUTTONDOWN) {
                            int mouseX, mouseY;
                            SDL_GetMouseState(&mouseX, &mouseY);

                            // Vérifiez si le clic est dans la zone du bouton "oui"
                            if (mouseX >= 1420 && mouseX <= 1450 && mouseY >= 200 && mouseY <= 260) {
                                reponse = "oui";
                                choixFait = true;
                            }
                            // Vérifiez si le clic est dans la zone du bouton "non"
                            else if (mouseX >= 1450 && mouseX <= 1480 && mouseY >= 200 && mouseY <= 260) {
                                reponse = "non";
                                choixFait = true;
                            }
                        }
                    }
                }
                if (reponse == "oui") {
                    if(entrees[i] == -1){
                        joueurs.retirerArgent(joueurIndex, 200);
                        entrees[i] = 0;
                        std::cout << "entree sur " << i << " est de " << entrees[i] << std::endl;
                        std::vector<std::string> totalPhrases;
                        totalPhrases.insert(totalPhrases.end(), phrases1.begin(), phrases1.end());
                        totalPhrases.insert(totalPhrases.end(), phrases2.begin(), phrases2.end());
                        gameRenderer.renderGame(joueurs, totalPhrases, 0, -1, typeHotel, entrees);
                    }
                        
                }
                else {
                    phrases1 = {"Vous avez decide de ne pas acheter d'entrées pour les hôtels."};
                    gameRenderer.renderGame(joueurs, phrases1, 0, -1, typeHotel, entrees);
                }
            }
        }
        
    }
}




void jouerPartie(SDL_Renderer* renderer, Renderer& gameRenderer) {
    // Création des joueurs
    Terrain terrain;
    Hotel hotel("hotel1");
    std::vector<std::string> nomsJoueurs = {"Alicia", "Charbel"};
    std::vector<int> argentsInitiaux = {7000, 7000};
    std::vector<int> positionsInitiales = {1, 1};
    Joueur joueurs(nomsJoueurs, argentsInitiaux, positionsInitiales);
    int resultatDe = 0;
    int resultatDe_special = -1;
    int construitHotel = -1;
    // Création du dé normal
    DeNormal deNormal;
    DeSpecial deSpecial;
    std::vector<bool> tableauBool(4, false);
    std::vector<int> occupTerrain = {-1, -1, -1, -1}; //pour savoir qui occupe le terrain, 0 pour joueur1 et 1 pour joueur2
    std::vector<int> prixLoyer = {100, 200, 300, 400};
    std::vector<int> typeHotel = {-1, -1, -1, -1}; //pour savoir le type de l'hotel, 0 pour hotel de base et 1 pour hotel annexe
    std::vector<int> entrees = {-1, -1, -1, -1}; //pour savoir s'il y'a des entrees construites sur les terrains
    //int increment_Joueur = {0, 0}; //pour savoir ou ils sont sur le plateau

    // Déroulement du jeu pour n tours
    for (int tour = 1; tour <= 20; ++tour) {
        std::vector<std::string> tourPhrases = {
            "********************************************",
            "Tour " + std::to_string(tour),
            "********************************************"
        };

        for (int i = 0; i < nomsJoueurs.size(); i++) {
            std::vector<std::string> joueurPhrases = {
                "C'est le tour du joueur " + std::to_string(i+1) + " - " + joueurs.getNom(i),
                "Le joueur " + joueurs.getNom(i) + " est a la case " + std::to_string(joueurs.getPosition(i)),
                "Veuillez lancer le de : "
            };
            std::vector<std::string> totalPhrases;
            totalPhrases.insert(totalPhrases.end(), tourPhrases.begin(), tourPhrases.end());
            totalPhrases.insert(totalPhrases.end(), joueurPhrases.begin(), joueurPhrases.end());
            gameRenderer.renderGame(joueurs, totalPhrases, resultatDe, resultatDe_special, typeHotel, entrees);
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
                        if (mouseX >= 800 && mouseX <= 950 && mouseY >= 10 && mouseY <= 60) {
                            // Clic détecté dans la zone "Jouer le dé", donc lancer le dé
                            int anciennePosition = joueurs.getPosition(i);
                            resultatDe = deNormal.lanceDe();
                            std::vector<std::string> dePhrases = {
                                "Le joueur avance de " + std::to_string(resultatDe) + " cases."
                            };
                            
                            // Mettre à jour la position du joueur
                            joueurs.setPosition(i, resultatDe);
                            int nouvellePosition = joueurs.getPosition(i);
                            //increment_Joueur[i] = increment_Joueur[i] + resultatDe;
                            passerParBanque(joueurs, i, anciennePosition, nouvellePosition, typeHotel, gameRenderer, entrees);
                            acheterEntreesHotels(joueurs, i, anciennePosition, nouvellePosition, typeHotel, gameRenderer, entrees, tableauBool, occupTerrain);
                            std::vector<std::string> positionPhrases = {
                                "Le joueur est maintenant a la case " + std::to_string(joueurs.getPosition(i))
                            };

                            if (joueurs.getPosition(i) != joueurs.getPosition((i + 1) % 2)) {
                                // Les joueurs ne sont pas sur la même case
                                std::vector<std::string> totalPhrases2;
                                totalPhrases2.insert(totalPhrases2.end(), tourPhrases.begin(), tourPhrases.end());
                                totalPhrases2.insert(totalPhrases2.end(), dePhrases.begin(), dePhrases.end());
                                totalPhrases2.insert(totalPhrases2.end(), positionPhrases.begin(), positionPhrases.end());
                                gameRenderer.renderGame(joueurs, totalPhrases2, resultatDe, resultatDe_special, typeHotel, entrees);
                            } else {
                                // Les joueurs sont sur la même case
                                // Mettre à jour la position du joueur
                                joueurs.setPosition(i, 1);
                                std::vector<std::string> memeCasePhrases = {
                                    "Le joueur se retrouve sur la meme case qu'un autre joueur.",
                                    "Il avance donc d'une case supplementaire.",
                                    "Le joueur est maintenant a la case " + std::to_string(joueurs.getPosition(i))
                                };
                                std::vector<std::string> totalPhrases3;
                                totalPhrases3.insert(totalPhrases3.end(), tourPhrases.begin(), tourPhrases.end());
                                totalPhrases3.insert(totalPhrases3.end(), dePhrases.begin(), dePhrases.end());
                                totalPhrases3.insert(totalPhrases3.end(), positionPhrases.begin(), positionPhrases.end());
                                totalPhrases3.insert(totalPhrases3.end(), memeCasePhrases.begin(), memeCasePhrases.end());
                                gameRenderer.renderGame(joueurs, totalPhrases3, resultatDe, resultatDe_special, typeHotel, entrees);
                                SDL_Delay(500);
                            }
                            
                            //----------------------------------------------------------------------------------------------------------------------------------------------//                            
                            std::string reponse;
                            bool estOccupe = false;
                            int numerocase = joueurs.getPosition(i);
                            const Terrain* terrainAdjacent = terrain.getTerrainAdjacent(numerocase);
                            int index = terrain.getTerrainIndex(numerocase);
                            std::cout << "index : " << index << std::endl;
                            if (terrainAdjacent != nullptr) {
                                // Utilisez le pointeur retourné pour accéder à m_estOccupe
                                estOccupe = terrainAdjacent->estOccupe();
                                if(numerocase == 12){
                                    std::vector<std::string> phrasesTerrain2 = {"Vous etes de passage à la banque" };
                                    gameRenderer.renderGame(joueurs, phrasesTerrain2, resultatDe, resultatDe_special, typeHotel, entrees);
                                }
                                else if(numerocase == 27){
                                    std::vector<std::string> phrasesTerrain2 = {"Vous etes de passage à la mairie" };
                                    gameRenderer.renderGame(joueurs, phrasesTerrain2, resultatDe, resultatDe_special, typeHotel, entrees);
                                }
                                else if ((tableauBool[index] == false) && (joueurs.getArgent(i) >= terrain.getPrix(numerocase))) {
                                    std::cout << "index tableaubool" << tableauBool[index] << std::endl;
                                    std::vector<std::string> phrasesTerrain = {"Le terrain est libre, il est a " + std::to_string(terrain.getPrix(numerocase)) + " euros souhaitez vous l'acheter? (oui/non)"};
                                    gameRenderer.renderGame(joueurs, phrasesTerrain, resultatDe, resultatDe_special, typeHotel, entrees);
                                    bool choixFait = false;
                                    while (!choixFait) {
                                        SDL_Event event;
                                        while (SDL_PollEvent(&event)) {
                                            if (event.type == SDL_MOUSEBUTTONDOWN) {
                                                int mouseX, mouseY;
                                                SDL_GetMouseState(&mouseX, &mouseY);

                                                // Vérifiez si le clic est dans la zone du bouton "oui"
                                                if (mouseX >= 1420 && mouseX <= 1450 && mouseY >= 10 && mouseY <= 60) {
                                                    reponse = "oui";
                                                    choixFait = true;
                                                }
                                                // Vérifiez si le clic est dans la zone du bouton "non"
                                                else if (mouseX >= 1450 && mouseX <= 1480 && mouseY >= 10 && mouseY <= 60) {
                                                    reponse = "non";
                                                    choixFait = true;
                                                }
                                            }
                                        }
                                    }
                                    if (reponse == "oui") {
                                        joueurs.retirerArgent(i, terrain.getPrix(numerocase));
                                        terrain.occupe(numerocase);
                                        tableauBool[index] = true; //le terrain devient occupé
                                        occupTerrain[index] = i; //pour savoir qui occupe le terrain, 0 pour joueur1 et 1 pour joueur2
                                        std::vector<std::string> phrasesTerrain2 = {
                                            "Le terrain est libre, il est a " + std::to_string(terrain.getPrix(numerocase)) + " euros souhaitez vous l'acheter? (oui/non)",
                                            "reponse : oui",
                                            "Vous avez achete le terrain",
                                            "Vous avez maintenant " + std::to_string(joueurs.getArgent(i)) + " euros"
                                            };
                                        gameRenderer.renderGame(joueurs, phrasesTerrain2, resultatDe, resultatDe_special, typeHotel, entrees);
                                    
                                        //------------------Achat hotel------------------------
                                        acheterHotel(joueurs, typeHotel, hotel, terrain, i, index, numerocase, gameRenderer, entrees);
                                    }
                                }
                                else if ((tableauBool[index] == false) && (joueurs.getArgent(i) < terrain.getPrix(numerocase))) {
                                    std::vector<std::string> phrasesTerrain2 = {"Le terrain n'est pas occupe mais vous n'avez pas les moyens pour l'acheter" };
                                    gameRenderer.renderGame(joueurs, phrasesTerrain2, resultatDe, resultatDe_special, typeHotel, entrees);
                                    //std::cout << "Le terrain n'est pas occupé mais vous n'avez pas les moyens pour l'acheter" << std::endl;
                                }
                                else {
                                    if (occupTerrain[index] == i) {
                                        
                                        std::vector<std::string> phrasesTerrain = {"Le terrain est deja occupe",
                                        "Vous etes le proprietaire de ce terrain"};
                                        gameRenderer.renderGame(joueurs, phrasesTerrain, resultatDe, resultatDe_special, typeHotel, entrees);
                                        //------------------Achat hotel------------------------
                                        acheterHotel(joueurs, typeHotel, hotel, terrain, i, index, numerocase, gameRenderer, entrees);
                                    }
                                    else {
                                        std::cout << "C'EST LE JOUEUR : " << occupTerrain[index] << "QUI OCCUPE LE TERRAIN" << std::endl;
                                        joueurs.retirerArgent(i, prixLoyer[index]);
                                        int deuxiemeJoueur = (i == 0) ? 1 : 0;
                                        joueurs.ajouterArgent(deuxiemeJoueur, prixLoyer[index]);

                                        std::vector<std::string> phrasesTerrain = {
                                            "Vous devez payer le loyer de " + std::to_string(prixLoyer[index]) + " euros",
                                            "Il vous reste " + std::to_string(joueurs.getArgent(i)) + " euros", 
                                            "Il reste a l'autre joueur " + std::to_string(joueurs.getArgent(deuxiemeJoueur)) + " euros",
                                            };
                                        gameRenderer.renderGame(joueurs, phrasesTerrain, resultatDe, resultatDe_special, typeHotel, entrees);
                                        SDL_Delay(1000); // Attendre 3 secondes
                                    }
                                }
                            }
                            else {
                                std::cerr << "Erreur : Terrain adjacent invalide." << std::endl;
                            }

                            //Relancer le dé s'il était égal à 6
                            if (resultatDe == 6) 
                            {
                                // Afficher un message pour indiquer que le joueur relance le dé
                                std::vector<std::string> relancePhrases = {
                                    "Vous avez obtenu un 6, vous devez relancer le de : "
                                };
                                gameRenderer.renderGame(joueurs, relancePhrases, resultatDe, resultatDe_special, typeHotel, entrees);
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
    gameRenderer.renderGame(joueurs, finPartiePhrases, resultatDe, resultatDe_special, typeHotel, entrees);
    SDL_Delay(3000); // Attendre 3 secondes avant de fermer la fenêtre
}
