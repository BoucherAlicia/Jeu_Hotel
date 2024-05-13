// terrain.hpp
#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <iostream>
#include <string>
#include <vector>

class Terrain {
protected:
    std::string m_nom; // Nom du terrain
    int m_prix;         // Prix d'achat du terrain
    bool m_estConstruit; // Indique si le terrain est construit
    bool m_estOccupe;    // Indique si le terrain est occupé par un joueur
    std::vector<Terrain> terrains;
    std::string m_propriete; // Propriété du terrain

public:
    // Constructeur
    Terrain();

    // Constructeur avec nom et prix
    Terrain(const std::string &nom, int prix, const std::string &propriete);

    // Getters
    std::string getNom(int numeroCase) const;
    int getPrix(int numeroCase) const;
    bool estConstruit() const;
    bool estOccupe() const;

    // Autres méthodes
    void occupe(int numeroCase);
    void construit(int numeroCase);
    void afficherInfo() const;
    const Terrain *getTerrainAdjacent(int numeroCase) const;
    int getTerrainIndex(int numeroCase) const;
private:
    void updateTerrainStatus(int numeroCase, bool estOccupe);
    
};

#endif
/*
//Joueur joueurs;
    int resultatDe = 0;
    int nombreJoueurs = 2;
    int resultatDe_special = -1;
    Terrain terrain;
    // Création du dé normal
    DeNormal deNormal;
    DeSpecial deSpecial;
    std::vector<bool> tableauBool(4);
    std::vector<int> prixLoyer = {100, 200, 300, 400};
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
                            }*/