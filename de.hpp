#ifndef DE_HPP
#define DE_HPP

#include <iostream>
//#include <cstdlib> //pour le rand

class De {
public:
    De(){};
    // Fonction pour lancer le dé
    virtual int lanceDe() = 0;

    // Implémentation de la méthode virtuelle utiliser
    virtual void utiliser() {
        lanceDe(); // Appelle la fonction lanceDe lors de l'utilisation
    }
};
#endif


