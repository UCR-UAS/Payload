all: main

Network.o: Network.h Network.cpp
	g++ Network.cpp -c

main: Network.o
	g++ main.cpp Network.o -o main

clean:
	rm *.o main