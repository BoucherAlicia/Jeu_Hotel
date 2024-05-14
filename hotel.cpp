// hotel.cpp

#include "hotel.hpp"
#include "plateau.hpp"

Hotel::Hotel(const std::string& nom){}

// Hotel::Hotel(const std::string& nom)
//     : Terrain(nom, prix, propriete) {} // Appel du constructeur de la classe de base Terrain

// Hotel::Hotel() { //constructeur par defaut
//     hotels.emplace_back("Hotel de base");
// }

void Hotel::construireHotel(int m_indexTerrain) {
        m_estConstruit = true;
        //afficher sur l'ecran
        //renderHotelAffiche(m_indexTerrain);
        std::cout << "Vous avez construit un hotel sur le terrain " << m_indexTerrain << std::endl;

}

