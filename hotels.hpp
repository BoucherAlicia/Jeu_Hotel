#ifndef HOTELS_HPP
#define HOTELS_HPP

#include "hotel.hpp"
#include <vector>

class Hotels {
private:
    std::vector<Hotel> proprietes;

public:
    Hotels();

    // Méthode pour acheter une propriété
    void acheterPropriete(int index) {
        proprietes[index].acheter();
    }
};

#endif // HOTELS_HPP
