#define main    SDL_main
#include "Game.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>

#undef main

int main(int argc, char* args[]) {

	Game *game = new Game();
	game->play();
	delete game;

	return 0;
}

