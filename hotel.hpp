// hotel.hpp

#ifndef HOTEL_HPP
#define HOTEL_HPP

#include "terrain.hpp" // Inclure la classe de base Terrain

class Hotel : public Terrain { // Hotel hérite de Terrain
public:
    // Constructeurs
    Hotel(const std::string& nom, int prix, const std::string& propriete);

    // Méthode pour construire un hôtel par un joueur donné
    void construireHotel(const std::string& joueur);
};

#endif
