#ifndef DENORMAL_HPP
#define DENORMAL_HPP

#include "de.hpp"
#include <iostream>
#include <cstdlib> //pour le rand


class DeNormal : public De {
public:
    DeNormal(){};
    // Fonction pour lancer le dé normal
    int lanceDe() override {
        srand(time(NULL));
        int resultat = rand() % 6 + 1; // Génère un nombre aléatoire entre 1 et 6
        //std::cout << "Le dé normal affiche : " << resultat << std::endl;
        return resultat;
    }
};
#endif