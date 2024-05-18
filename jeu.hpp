#ifndef JEU_HPP
#define JEU_HPP
#include "plateau.hpp"

void jouerPartie(SDL_Renderer* renderer, Renderer& gameRenderer);
void acheterHotel(Joueur& joueurs, std::vector<int>& typeHotel, Hotel& hotel, Terrain& terrain, int i, int index, int numerocase, Renderer& gameRenderer);

#endif