exec = executable.exe
libs = -lsfml-graphics -lsfml-window -lsfml-system

.PHONY: all run

all: # makes the compilation
	g++ -c *.cpp -std=c++20
	g++ *.o $(libs) -o $(exec)
run: all # compiles and then run the executable
	./$(exec)
