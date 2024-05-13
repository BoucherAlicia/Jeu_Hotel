CPP=g++
LD=g++

CPPFLAGS=-std=c++14
LDFLAGS=-std=c++14
LIBS=-lSDL2 -lSDL2_ttf -lSDL2_image


all: hotel

hotel: main.o terrain.o plateau.o case.o hotel.o
	$(LD) $(LDFLAGS) main.o terrain.o plateau.o case.o hotel.o -o hotel $(LIBS)

main.o: main.cpp terrain.hpp plateau.hpp case.hpp hotel.hpp
	$(CPP) $(CPPFLAGS) -c main.cpp

terrain.o: terrain.cpp terrain.hpp
	$(CPP) $(CPPFLAGS) -c terrain.cpp

plateau.o: plateau.cpp plateau.hpp
	$(CPP) $(CPPFLAGS) -c plateau.cpp

case.o: case.hpp case.cpp
	$(CPP) $(CPPFLAGS) -c case.cpp

hotel.o: hotel.hpp hotel.cpp
	$(CPP) $(CPPFLAGS) -c hotel.cpp
clean:
	rm -f *.o hotel
