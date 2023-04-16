all : test

test : main.o funcs.o
	g++ main.o funcs.o -o test

main.o : main.cpp
	g++ -c main.cpp

funcs.o : funcs.cpp
	g++ -c funcs.cpp

clean :
	rm -rf *.o test