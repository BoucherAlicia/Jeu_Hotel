CPP=g++
LD=g++

CPPFLAGS=-std=c++14
LDFLAGS=-std=c++14
LIBS=-lSDL2 -lSDL2_ttf -lSDL2_image


all: hotel

hotel: main.o hotel.o hotels.o plateau.o case.o
	$(LD) $(LDFLAGS) main.o hotel.o hotels.o plateau.o case.o -o hotel $(LIBS)

main.o: main.cpp hotel.hpp hotels.hpp plateau.hpp case.hpp
	$(CPP) $(CPPFLAGS) -c main.cpp

hotel.o: hotel.cpp hotel.hpp
	$(CPP) $(CPPFLAGS) -c hotel.cpp

hotels.o: hotels.cpp hotels.hpp
	$(CPP) $(CPPFLAGS) -c hotels.cpp

plateau.o: plateau.cpp plateau.hpp
	$(CPP) $(CPPFLAGS) -c plateau.cpp

case.o: case.hpp case.cpp
	$(CPP) $(CPPFLAGS) -c case.cpp

clean:
	rm -f *.o hotel
