// Hotel.cpp

#include "hotel.hpp"
#include <iostream>

// Constructeur
Hotel::Hotel() {
    // Appel de la méthode d'initialisation de l'hôtel
    initialize();
}

// Destructeur
Hotel::~Hotel() {
    // Nettoyage éventuel, si nécessaire
}

// Méthode pour initialiser l'hôtel
void Hotel::initialize() {
    // Création de quelques chambres d'hôtel de test
    for (int i = 0; i < 10; ++i) {
        Room room;
        room.roomNumber = i + 1;
        room.guestName = "";
        room.occupied = false;
        rooms.push_back(room);
    }
}

// Méthode pour afficher l'état de l'hôtel
void Hotel::displayStatus() const {
    std::cout << "Hotel Status:" << std::endl;
    for (const auto& room : rooms) {
        std::cout << "Room " << room.roomNumber << ": ";
        if (room.occupied) {
            std::cout << "Occupied by " << room.guestName << std::endl;
        } else {
            std::cout << "Available" << std::endl;
        }
    }
}

// Implémentez ici d'autres méthodes pour la logique du jeu...
