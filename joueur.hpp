#ifndef JOUEUR_HPP
#define JOUEUR_HPP

#include <string>
#include <vector>
#include <iostream>
#include <SDL2/SDL.h>

class Joueur {
private:
    std::vector<std::string> noms; //tableau de noms
    std::vector<int> argents;
    std::vector<std::vector<int>> hotelsPossedes; // Liste des indices des hôtels possédés par le joueur
    std::vector<int> positions;

public:
    // Constructeur prenant en charge plusieurs joueurs
    Joueur(const std::vector<std::string>& nomsJoueurs, const std::vector<int>& argentsInitiaux, const std::vector<int>& positionsInitiales) 
        : noms(nomsJoueurs), argents(argentsInitiaux), positions(positionsInitiales) {
        // Initialisation de la liste des hôtels possédés pour chaque joueur
        hotelsPossedes.resize(noms.size());
    }

    // Accesseurs
    const std::string& getNom(int joueur) const { return noms[joueur]; }
    int getArgent(int joueur) const { return argents[joueur]; }
    const std::vector<int>& getHotelsPossedes(int joueur) const { return hotelsPossedes[joueur]; }
    int getPosition(int joueur) const { return positions[joueur]; }

    // Méthodes pour gérer l'argent
    void ajouterArgent(int joueur, int montant) { argents[joueur] += montant; }
    void retirerArgent(int joueur, int montant) { argents[joueur] -= montant; }

    // Méthode pour gérer les hôtels possédés
    void ajouterHotel(int joueur, int indiceHotel) { hotelsPossedes[joueur].push_back(indiceHotel); }

    // Méthode pour définir la position du joueur
    void setPosition(int joueur, int resultatDe);


};
#endif