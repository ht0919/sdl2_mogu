CXX = gcc

CXXFLAGS = -Wall -I include
LDFLAGS = -L /usr/local/lib -l SDL2-2.0.0 -l SDL2_ttf-2.0.0 -l SDL2_mixer-2.0.0

all: mogu

mogu: mogu_main.o mogu_back.o mogu_enemy.o mogu_judg.o mogu_music.o mogu_text.o
	$(CXX) mogu_main.o mogu_back.o mogu_enemy.o mogu_judg.o mogu_music.o mogu_text.o -o mogu $(LDFLAGS)

mogu_main.o : mogu_main.c mogu.h
	$(CXX) $(CXXFLAGS) -c mogu_main.c -o mogu_main.o
mogu_back.o : mogu_back.c mogu.h
	$(CXX) $(CXXFLAGS) -c mogu_back.c -o mogu_back.o
mogu_enemy.o : mogu_enemy.c mogu.h
	$(CXX) $(CXXFLAGS) -c mogu_enemy.c -o mogu_enemy.o
mogu_judg.o : mogu_judg.c mogu.h
	$(CXX) $(CXXFLAGS) -c mogu_judg.c -o mogu_judg.o
mogu_music.o : mogu_music.c mogu.h
	$(CXX) $(CXXFLAGS) -c mogu_music.c -o mogu_music.o
mogu_text.o : mogu_text.c mogu.h
	$(CXX) $(CXXFLAGS) -c mogu_text.c -o mogu_text.o

clean:
	rm -f mogu_main.o mogu_back.o mogu_enemy.o mogu_judg.o mogu_music.o mogu_text.o mogu
