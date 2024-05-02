// Hotel.h

#ifndef HOTEL_H
#define HOTEL_H

#include <vector>
#include <string>

// Déclaration de la classe Hotel
class Hotel {
public:
    // Constructeur
    Hotel();

    // Destructeur
    ~Hotel();

    // Méthode pour initialiser l'hôtel
    void initialize();

    // Méthode pour afficher l'état de l'hôtel
    void displayStatus() const;

    // Autres méthodes pour la logique du jeu...

private:
    // Définition d'une structure pour une chambre d'hôtel
    struct Room {
        int roomNumber;
        std::string guestName;
        bool occupied;
    };

    // Vecteur pour stocker les chambres de l'hôtel
    std::vector<Room> rooms;
};

#endif // HOTEL_H
