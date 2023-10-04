exec = executable.exe
libs = -lsfml-graphics -lsfml-window -lsfml-system

.PHONY: all run

all: # makes the compilation
	g++ -c main.cpp
	g++ main.o -o $(exec) $(libs)
run: all # compiles and then run the executable
	./$(exec)
