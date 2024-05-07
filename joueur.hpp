#include <string>
#include <vector>

class Joueur {
private:
    std::string nom;
    int argent;
    std::vector<int> hotelsPossedes; // Liste des indices des hôtels possédés par le joueur

public:
    Joueur(const std::string& nomJoueur, int argentInitial) : nom(nomJoueur), argent(argentInitial) {}

    // Accesseurs
    const std::string& getNom() const { return nom; }
    int getArgent() const { return argent; }
    const std::vector<int>& getHotelsPossedes() const { return hotelsPossedes; }

    // Méthodes pour gérer l'argent
    void ajouterArgent(int montant) { argent += montant; }
    void retirerArgent(int montant) { argent -= montant; }

    // Méthode pour gérer les hôtels possédés
    void ajouterHotel(int indiceHotel) { hotelsPossedes.push_back(indiceHotel); }
};
