#include "de_normal.hpp" 


class DeSpecial : public De {
public:
    // Redéfinition de la fonction lanceDe pour le dé spécial
    int lanceDe() override {
        srand(time(NULL));
        std::string faces[6] = {"rouge", "vert", "vert", "vert", "H", "2D"};

        // Génère un nombre aléatoire entre 0 et 5 pour sélectionner une face du dé
        int index = rand() % 6;

        // Affiche la face sélectionnée
        std::cout << "Le dé spécial affiche : " << faces[index] << std::endl;
        return index;
    }
};
