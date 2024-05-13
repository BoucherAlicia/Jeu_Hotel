// hotel.hpp

#ifndef HOTEL_HPP
#define HOTEL_HPP

#include "terrain.hpp" // Inclure la classe de base Terrain

class Hotel : public Terrain { // Hotel hérite de Terrain

private:
    std::string m_propriete; // Propriétaire de l'hôtel
    int m_indexTerrain; // Index du terrain

public:
    // Constructeurs
    Hotel(const std::string& nom, int prix, const std::string& propriete);

    // Méthode pour construire un hôtel par un joueur donné
    void construireHotel(int m_indexTerrain, const std::string& joueur);
};

#endif

