#include <string>

class Propriete {
protected:
    std::string nom;
    int prix;

public:
    Propriete(const std::string& nomPropriete, int prixPropriete) : nom(nomPropriete), prix(prixPropriete) {}

    // Méthode virtuelle pure pour l'achat de la propriété
    virtual void acheter() = 0;

    // Accesseurs
    const std::string& getNom() const { return nom; }
    int getPrix() const { return prix; }
};
