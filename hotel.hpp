<<<<<<< HEAD
=======
#ifndef HOTEL_HPP
#define HOTEL_HPP

#include "propriete.hpp"
#include <iostream>

class Hotel {
private:
    std::string nom;
    int prixTerrain;
    int prixHotel1;
    int prixHotel2;
    int prixEentree;

public:
    Hotel(const std::string& nom, int prixTerrain, int prixHotel1, int prixHotel2, int prixEentree)
        : prixTerrain(prixTerrain), prixHotel1(prixHotel1), prixHotel2(prixHotel2), prixEentree(prixEentree) {}

    // Méthode pour acheter la propriété
    void acheter() {
        std::cout << "Achat de la propriete : " << nom << std::endl;
        // Ajoutez ici la logique pour l'achat de la propriété
    }
};

#endif
>>>>>>> c0631ad2d1e1bb3b46e8adad67a9369d949a867a
