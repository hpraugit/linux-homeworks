all: main

main: main.o complex.o complexsort.o
	g++ main.o complex.o complexsort.o -o main

main.o: main.cpp
	g++ -c main.cpp

complex.o: complex.cpp
	g++ -c complex.cpp

complexsort.o: complexsort.cpp
	g++ -c complexsort.cpp

clean: 
	rm  *.o main
