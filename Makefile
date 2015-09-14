all: icoordstrans test

icoordstrans: main.o main_types.o corefuncs.o
	g++ -shared -O -o libicoordstrans.so main.o main_types.o corefuncs.o -lm

test: test.o
	g++ -L . -O -o test test.o -licoordstrans

main.o: main.cpp
	g++ -c main.cpp

main_types.o: main_types.cpp
	g++ -c main_types.cpp

corefuncs.o: corefuncs.cpp
	g++ -c corefuncs.cpp

test.o: test.c
	g++ -c test.c

clean:
	rm -f corefuncs.o main_types.o main.o icoordstrans.so test.o test

