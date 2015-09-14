all: icoordstrans test

icoordstrans: main.o main_types.o corefuncs.o
	g++ -fPIC -shared -O -o libicoordstrans.so main.o main_types.o corefuncs.o -lm

test: test.o
	g++ -fPIC -L . -O -o test test.o -licoordstrans

main.o: main.cpp
	g++ -fPIC -c main.cpp

main_types.o: main_types.cpp
	g++ -fPIC -c main_types.cpp

corefuncs.o: corefuncs.cpp
	g++ -fPIC -c corefuncs.cpp

test.o: test.c
	g++ -fPIC -c test.c

clean:
	rm -fv corefuncs.o main_types.o main.o icoordstrans.so libicoordstrans.so test.o test

