// hotel.cpp

#include "hotel.hpp"

Hotel::Hotel(const std::string& nom, int prix, const std::string& propriete)
    : Terrain(nom, prix, propriete) {} // Appel du constructeur de la classe de base Terrain

void Hotel::construireHotel(const std::string& joueur) {
    // Vérifier si le terrain est occupé par le joueur donné
    if (m_estOccupe && m_propriete == joueur) {
        // Construire l'hôtel
        m_estConstruit = true;
        std::cout << "Un hôtel a été construit sur " << m_nom << " par " << joueur << std::endl;
    } else {
        // Afficher un message d'erreur si le terrain n'est pas occupé par le joueur donné
        std::cerr << "Impossible de construire un hôtel sur " << m_nom << ". Le terrain n'est pas occupé par " << joueur << "." << std::endl;
    }
}
