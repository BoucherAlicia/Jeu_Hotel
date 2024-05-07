#include "objet.hpp"
#include <iostream>
#include <cstdlib> //pour le rand

class De : public Objet {
public:
    De(){};
    // Fonction pour lancer le dé
    virtual int lanceDe() = 0;

    // Implémentation de la méthode virtuelle utiliser
    void utiliser() override {
        lanceDe(); // Appelle la fonction lanceDe lors de l'utilisation
    }
};



