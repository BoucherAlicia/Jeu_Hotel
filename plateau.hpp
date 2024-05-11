#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>

#include <SDL2/SDL_image.h>
#include <sstream>

#include "case.hpp"
#include "jeu.cpp"

class Renderer {
public:
    Renderer(SDL_Renderer* renderer, int width, int height);
    ~Renderer();

    void renderGame(const Joueur& joueurs, const std::vector<std::string>& phrases, int resultat_de, int resultat_de_special);
 

private:
    SDL_Renderer* m_renderer;
    int m_width;
    int m_height;
    std::vector<SDL_Rect> m_trackRects;
    std::vector<SDL_Rect> m_hotelRects;
    std::vector<std::string> m_hotelNames;
    TTF_Font* m_font; // Déclaration de la police de caractères
    TTF_Font* m_font2; // Déclaration de la police de caractères

    void initTrackRects();
    void initHotelNames();
    void renderTrack();
    void renderHotels();
    void renderDe(int resultat_de, int resultat_de_special);
    void renderTable();
    void renderCases();
    void afficherPion(const Joueur& joueurs) const;
    void renderTerminal(const std::vector<std::string>& phrases);
};

#endif // RENDERER_HPP
