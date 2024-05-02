CPP=g++
LD=g++

CPPFLAGS=-std=c++14
LDFLAGS=-std=c++14
LIBS=-lSDL2 -lSDL2_ttf -lSDL2_image


all: hotel

hotel: main.o hotel.o plateau.o
	$(LD) $(LDFLAGS) main.o hotel.o plateau.o -o hotel $(LIBS)

main.o: main.cpp hotel.hpp plateau.hpp
	$(CPP) $(CPPFLAGS) -c main.cpp

hotel.o: hotel.cpp hotel.hpp
	$(CPP) $(CPPFLAGS) -c hotel.cpp

plateau.o: plateau.cpp plateau.hpp
	$(CPP) $(CPPFLAGS) -c plateau.cpp


clean:
	rm -f *.o hotel
