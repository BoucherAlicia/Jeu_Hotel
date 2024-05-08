// terrain.cpp

#include "terrain.hpp"
#include "case.hpp"
#include "plateau.hpp"



//Terrain::Terrain(std::string nom, int prix) : m_nom(nom), m_prix(prix), m_estOccupe(false), m_estConstruit(false) {}
Terrain::Terrain(const std::string& nom, int prix)
    : m_nom(nom), m_prix(prix), m_estOccupe(false), m_estConstruit(false) {}

Terrain::Terrain() {
    terrains.emplace_back("Hotel1", 1000);
    terrains.emplace_back("Hotel2", 1500);
    terrains.emplace_back("Hotel3", 2000);
    terrains.emplace_back("Hotel4", 3000);
}

void Terrain::occupe(int numeroCase) {
    if (numeroCase < 1) {
        std::cerr << "Erreur : numeroCase invalide." << std::endl;
        return;
    }
    else if (numeroCase >= 1 && numeroCase < 4) {
        terrains[0].m_estOccupe = true;
    }
    else if (numeroCase >= 5 && numeroCase < 12) {
        terrains[1].m_estOccupe = true;
    } 
    else if (numeroCase >= 13 && numeroCase < 20) {
        terrains[2].m_estOccupe = true;
    }
    else if (numeroCase >= 20 && numeroCase < 27) {
        terrains[3].m_estOccupe = true;
    }   
}

void Terrain::construit(int numeroCase) {
    if (numeroCase < 1) {
            std::cerr << "Erreur : numeroCase invalide." << std::endl;
            return;
        }
        else if (numeroCase >= 1 && numeroCase < 4) {
            terrains[0].m_estConstruit = true;
        }
        else if (numeroCase >= 5 && numeroCase < 12) {
            terrains[1].m_estConstruit = true;
        } 
        else if (numeroCase >= 13 && numeroCase < 20) {
            terrains[2].m_estConstruit = true;
        }
        else if (numeroCase >= 20 && numeroCase < 27) {
            terrains[3].m_estConstruit = true;
        }   
}

std::string Terrain::getNom() const { //A CONTINUER SELON LE NUMERO DE CASE
    return m_nom;
}

int Terrain::getPrix() const { //A CONTINUER SELON LE NUMERO DE CASE
    return m_prix;
}

void Terrain::afficherInfo() const {
    std::cout << "Terrain : " << m_nom << ", Prix : " << m_prix << ", Occupé : " << (m_estOccupe ? "Oui" : "Non") << ", Construit : " << (m_estConstruit ? "Oui" : "Non") << std::endl;
}

const Terrain* Terrain::getTerrainAdjacent(int numeroCase) const {
    if (numeroCase < 1) {
        return nullptr; // Aucune case à gauche de la première case
    }
    else if (numeroCase >= 1 && numeroCase < 4) {
        terrains[0].afficherInfo();
    }
    else if (numeroCase >= 5 && numeroCase < 12) {
        terrains[1].afficherInfo();
    } 
    else if (numeroCase >= 13 && numeroCase < 20) {
        terrains[2].afficherInfo();
    }
    else if (numeroCase >= 20 && numeroCase < 27) {
        terrains[3].afficherInfo();
    }   
    return nullptr; // Aucun terrain correspondant trouvé
}
