// terrain.hpp
#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <iostream>
#include <string>
#include <vector>

class Terrain {
    protected:
        std::string m_nom; // Nom du terrain
        int m_prix; // Prix d'achat du terrain
        bool m_estConstruit; // Indique si le terrain est construit
        bool m_estOccupe; // Indique si le terrain est occupé par un joueur
        std::vector<Terrain> terrains;
    

    public:
        // Constructeur
        Terrain();

        // Constructeur avec nom et prix
        Terrain(const std::string& nom, int prix);

        // Getters
        std::string getNom() const;
        int getPrix() const;
        bool estConstruit() const;
        bool estOccupe() const;

        // Setters
        void setEstConstruit(bool estConstruit);
        void setEstOccupe(bool estOccupe);

        // Autres méthodes
        void occupe(int numeroCase);
        void construit(int numeroCase);
        void afficherInfo() const;
        const Terrain* getTerrainAdjacent(int numeroCase) const;

};

#endif