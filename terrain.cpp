// terrain.cpp

#include "terrain.hpp"

Terrain::Terrain(const std::string& nom, int prix)
    : m_nom(nom), m_prix(prix), m_estOccupe(false), m_estConstruit(false) {}

Terrain::Terrain() {
    terrains.emplace_back("Hotel1", 1000);
    terrains.emplace_back("Hotel2", 1500);
    terrains.emplace_back("Hotel3", 2000);
    terrains.emplace_back("Hotel4", 3000);
}

void Terrain::afficherInfo() const {
        //std::cout << "Terrain : " << m_nom << ", Prix : " << m_prix << ", Occupé : " << (m_estOccupe ? "Oui" : "Non") << ", Construit : " << (m_estConstruit ? "Oui" : "Non") << std::endl;
}

int Terrain::getTerrainIndex(int numeroCase) const {
    if (numeroCase < 1 || numeroCase > 30) {
        return -1;
    } else if ((numeroCase >= 1 && numeroCase <= 4) || (numeroCase > 27 && numeroCase <= 30)) {
        return 0;
    } else if (numeroCase > 4 && numeroCase <= 12) {
        return 1;
    } else if (numeroCase >= 13 && numeroCase < 20) {
        return 2;
    } else if (numeroCase >= 20 && numeroCase <= 27) {
        return 3;
    }
    return -1;
}

void Terrain::updateTerrainStatus(int numeroCase, bool estOccupe) {
    int terrainIndex = getTerrainIndex(numeroCase);
    if (terrainIndex != -1) {
        terrains[terrainIndex].m_estOccupe = estOccupe;
    } else {
        std::cerr << "Erreur : numeroCase invalide." << std::endl;
    }
}

void Terrain::occupe(int numeroCase) {
    updateTerrainStatus(numeroCase, true);
}

void Terrain::construit(int numeroCase) {
    updateTerrainStatus(numeroCase, true);
}

std::string Terrain::getNom(int numeroCase) const {
    int terrainIndex = getTerrainIndex(numeroCase);
    if (terrainIndex != -1) {
        return terrains[terrainIndex].m_nom;
    } else {
        return "Terrain inexistant";
    }
}

int Terrain::getPrix(int numeroCase) const {
    int terrainIndex = getTerrainIndex(numeroCase);
    if (terrainIndex != -1) {
        return terrains[terrainIndex].m_prix;
    } else {
        return -1; // Prix invalide
    }
}

const Terrain* Terrain::getTerrainAdjacent(int numeroCase) const {
    int terrainIndex = getTerrainIndex(numeroCase);
    if (terrainIndex != -1) {
        terrains[terrainIndex].afficherInfo();
        return &terrains[terrainIndex];
    } else {
        std::cerr << "Erreur : numeroCase invalide." << std::endl;
        throw std::runtime_error("NumeroCase invalide.");
    }
}

bool Terrain::estOccupe() const {
    return m_estOccupe;
}

bool Terrain::estConstruit() const {
    return m_estConstruit;
}
