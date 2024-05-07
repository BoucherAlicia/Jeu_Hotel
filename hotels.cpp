#include "hotels.hpp"

Hotels::Hotels()
{
    // Ajoutez ici les différentes propriétés avec leurs prix
    proprietes.push_back(Hotel("hotel1", 1500, 2400, 1000, 100));
    proprietes.push_back(Hotel("hotel2", 1000, 2000, 900, 50));
    proprietes.push_back(Hotel("hotel3", 1100, 2200, 1000, 100));
    proprietes.push_back(Hotel("hotel4", 2000, 3000, 1500, 100));
}
