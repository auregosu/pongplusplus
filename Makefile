WINDOWSCC=x86_64-w64-mingw32-g++
CC:=g++
FLAGS:=--std=c++17
LIB:=-ipthread -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network
LIB2:=-lsfml-system -lsfml-window -lsfml-graphics -lsfml-network
SRC:=$(wildcard src/*.cpp)
OBJ:=$(SRC:src/%.cpp=obj/%.o)
OBJW:=$(SRC:src/%.cpp=objw/%.o)
SFMLPATH=~/Descargas/Libraries/SFML-2.5.1-MinGW-64/

bin/Windows/pong.exe: $(OBJW)
	$(WINDOWSCC) $^ $(FLAGS) -L $(SFMLPATH)lib $(LIB2) -o $@

linux: bin/linux/main

bin/linux/main: $(OBJ)
	$(CC) $(FLAGS) $^ -L $(LIB) -o $@

objw/%.o: src/%.cpp
	$(WINDOWSCC) $^ $(FLAGS) -c -I $(SFMLPATH)include -I include -L $(SFMLPATH)lib $(LIB2) -o $@

obj/%.o: src/%.cpp
	$(CC) $^ $(FLAGS) -c -I include -L $(LIB) -o $@

clear:
	rm obj/*.o | rm objw/*.o

#src/%.cpp: include/%.h

#main: $(wildcard obj/*.o)
#	g++ obj/*.o $(FLAGS) -o main
