all:
	g++ -Wall -std=c++11 main.cpp mf.cpp -Imf.h -I/usr/include/c++/4.2.1/eigen -omain.o
