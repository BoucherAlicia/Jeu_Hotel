#include "hotel.hpp"
/*
void Hotel::acheter(int index)
{
    if (index < 0 || index >= 4) {
        std::cout << "Index d'hotel invalide." << std::endl;
        return;
    }

    switch(index) {
        case 0: // Achat terrain
            if (m_terrainAchete) {
                std::cout << "Le terrain a déjà été acheté." << std::endl;
            } else {
                if (m_argent >= 1500) {
                    m_argent -= 1500;
                    m_terrainAchete = true;
                    std::cout << "Terrain acheté avec succès." << std::endl;
                } else {
                    std::cout << "Pas assez d'argent pour acheter le terrain." << std::endl;
                }
            }
            break;
        case 1: // Achat 1er hotel
            if (m_1erHotelAchete) {
                std::cout << "Le premier hotel a déjà été acheté." << std::endl;
            } else {
                if (m_argent >= 2400) {
                    m_argent -= 2400;
                    m_1erHotelAchete = true;
                    std::cout << "Premier hotel acheté avec succès." << std::endl;
                } else {
                    std::cout << "Pas assez d'argent pour acheter le premier hotel." << std::endl;
                }
            }
            break;
        case 2: // Achat 2eme hotel
            if (m_2emeHotelAchete) {
                std::cout << "Le deuxième hotel a déjà été acheté." << std::endl;
            } else {
                if (m_argent >= 1000) {
                    m_argent -= 1000;
                    m_2emeHotelAchete = true;
                    std::cout << "Deuxième hotel acheté avec succès." << std::endl;
                } else {
                    std::cout << "Pas assez d'argent pour acheter le deuxième hotel." << std::endl;
                }
            }
            break;
        case 3: // Achat 1 entrée
            if (m_argent >= 100) {
                m_argent -= 100;
                m_nbEntrees++;
                std::cout << "Une entrée achetée avec succès." << std::endl;
            } else {
                std::cout << "Pas assez d'argent pour acheter une entrée." << std::endl;
            }
            break;
        default:
            std::cout << "Index d'hotel invalide." << std::endl;
            break;
    }
}*/