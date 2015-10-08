all: main.cpp
	colorgcc -std=c++11 -I/usr/include -L/usr/lib/x86_64-linux-gnu -o Engine main.cpp -lstdc++ -lm -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net -lGL

run: Engine
	./Engine

clean: SIM
	rm ./Engine
