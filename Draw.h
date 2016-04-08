#pragma once
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include <vector>
#include "Board.h"
#undef main

using namespace std;
const int width = 750;
const int height = 950;

class Draw
{
private:
	SDL_Window *window;
	SDL_Texture *backgroundImage;
	SDL_Renderer *renderTarget;
	SDL_Texture *texture;
	SDL_Texture *snakeBody;
	SDL_Texture *snakeHeadDown;
	SDL_Texture *snakeHeadUp;
	SDL_Texture *snakeHeadLeft;
	SDL_Texture *snakeHeadRight;
	SDL_Texture *snakeTail;
	SDL_Texture *apple;
	SDL_Texture *banana;
	SDL_Texture *bomb;
	vector<class Field*>::iterator iterator;
public:
	Draw();
	~Draw();
	void setConsole(int width, int height);
	void setBackground(int width, int height, Board *board);


};

