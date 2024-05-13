CPP=g++
LD=g++

CPPFLAGS=-std=c++14
LDFLAGS=-std=c++14
LIBS=-lSDL2 -lSDL2_ttf -lSDL2_image


all: hotel

<<<<<<< HEAD
hotel: main.o terrain.o plateau.o case.o
	$(LD) $(LDFLAGS) main.o terrain.o plateau.o case.o -o hotel $(LIBS)

main.o: main.cpp terrain.hpp plateau.hpp case.hpp
	$(CPP) $(CPPFLAGS) -c main.cpp

=======
hotel: main.o terrain.o plateau.o case.o jeu.o joueur.o
	$(LD) $(LDFLAGS) main.o terrain.o plateau.o case.o jeu.o joueur.o -o hotel $(LIBS)

main.o: main.cpp terrain.hpp plateau.hpp case.hpp jeu.cpp joueur.cpp
	$(CPP) $(CPPFLAGS) -c main.cpp
	
>>>>>>> c0631ad2d1e1bb3b46e8adad67a9369d949a867a
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
