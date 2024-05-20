#include "joueur.hpp"

// Méthode pour définir la position du joueur
void Joueur::setPosition(int joueur, int resultatDe) {
    int nouvelleposition = positions[joueur] + resultatDe; 
    // Mettre à jour la position en s'assurant qu'elle reste dans les limites
    positions[joueur] = nouvelleposition % 30;
    if (positions[joueur] == 0) {
        positions[joueur] = 30;
    }
    //std::cout << "Vous êtes est maintenant à la case " << positions[joueur]<< std::endl;

}