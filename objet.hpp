#ifndef OBJET_HPP
#define OBJET_HPP

#include <string>

class Objet {
public:
    Objet(){};
    Objet(const std::string& nom, int valeur) : nom(nom), valeur(valeur) {}
    virtual ~Objet() {}

    // Getters pour les attributs
    const std::string& getNom() const { return nom; }
    int getValeur() const { return valeur; }

    virtual void utiliser() = 0; // Méthode virtuelle pure

protected:
    std::string nom;
    int valeur;
};
#endif