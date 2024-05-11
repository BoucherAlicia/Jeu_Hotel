CPP=g++
LD=g++

CPPFLAGS=-std=c++14
LDFLAGS=-std=c++14
LIBS=-lSDL2 -lSDL2_ttf -lSDL2_image


all: hotel

hotel: main.o terrain.o plateau.o case.o jeu.o joueur.o
	$(LD) $(LDFLAGS) main.o terrain.o plateau.o case.o jeu.o joueur.o -o hotel $(LIBS)

main.o: main.cpp terrain.hpp plateau.hpp case.hpp jeu.cpp joueur.cpp
	$(CPP) $(CPPFLAGS) -c main.cpp
	
terrain.o: terrain.cpp terrain.hpp
	$(CPP) $(CPPFLAGS) -c terrain.cpp

plateau.o: plateau.cpp plateau.hpp
	$(CPP) $(CPPFLAGS) -c plateau.cpp

jeu.o: jeu.cpp
	$(CPP) $(CPPFLAGS) -c jeu.cpp

joueur.o: joueur.cpp joueur.hpp
	$(CPP) $(CPPFLAGS) -c joueur.cpp

case.o: case.hpp case.cpp
	$(CPP) $(CPPFLAGS) -c case.cpp

clean:
	rm -f *.o hotel
