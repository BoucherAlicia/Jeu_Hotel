// terrain.cpp

#include "terrain.hpp"
#include "jeu.hpp"

Terrain::Terrain(const std::string& nom, int prix, const std::string& propriete)
    : m_nom(nom), m_prix(prix), m_propriete(propriete), m_estOccupe(false), m_estConstruit(false) {}

Terrain::Terrain() { //constructeur par defaut
    terrains.emplace_back("Hotel1", 1000, "Personne");
    terrains.emplace_back("Hotel2", 1500, "Personne");
    terrains.emplace_back("Hotel3", 2000, "Personne");
    terrains.emplace_back("Hotel4", 3000, "Personne");
}

void Terrain::afficherInfo() const {
        std::cout << "Terrain : " << m_nom << ", Prix : " << m_prix << ", Propriété :" << m_propriete << ", Occupé : " << (m_estOccupe ? "Oui" : "Non") << ", Construit : " << (m_estConstruit ? "Oui" : "Non") << std::endl;
}

int Terrain::getTerrainIndex(int numeroCase) const { //pour eviter les repetition du code
<<<<<<< HEAD
    if (numeroCase < 1 || numeroCase > 30) {
=======
    if (numeroCase < 1 || numeroCase > 27) {
>>>>>>> a2dc3b6 (Update classe terrain)
        return -1;
    } else if (numeroCase >= 1 && numeroCase <= 4) {
        return 0;
    } else if (numeroCase >= 5 && numeroCase <= 12) {
        return 1;
    } else if (numeroCase >= 13 && numeroCase < 20) {
        return 2;
    } else if (numeroCase >= 20 && numeroCase <= 30) {
        return 3;
    }
    return -1;
}

void Terrain::updateTerrainStatus(int numeroCase, bool estOccupe) { //pour mettre a jour si le terrain est occupé ou non
    int terrainIndex = getTerrainIndex(numeroCase);                 
    if (terrainIndex != -1) {
        terrains[terrainIndex].m_estOccupe = estOccupe;
<<<<<<< HEAD
        terrains[terrainIndex].m_propriete = "joueurs.getNom(0)"; //A MODIFIER POUR AFFICHER LE NOM DU JOUEUR QUI OCCUPERA LE TERRAIN
=======
        terrains[terrainIndex].m_propriete = "Joueur1"; //A MODIFIER POUR AFFICHER LE NOM DU JOUEUR QUI OCCUPERA LE TERRAIN
>>>>>>> a2dc3b6 (Update classe terrain)
    } else {
        std::cerr << "Erreur : numeroCase invalide." << std::endl;
    }
}

bool Terrain::estOccupe() const {
    return m_estOccupe;
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
    } else {
        std::cerr << "Erreur : numeroCase invalide." << std::endl;
        return nullptr;
    }
}
