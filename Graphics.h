#include <SDL.h>
#include <SDL_image.h>
#include <SDL_Mixer.h>
#include <SDL_ttf.h>
#include <windows.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include "Board.h"
using namespace std;


const int SCREEN_WIDTH = 750;
const int SCREEN_HEIGHT = 950;


class Graphics
{
private:
	SDL_DisplayMode DM;

	SDL_Window *window;
	SDL_Texture *backgroundImage;
	SDL_Renderer *renderTarget;
	SDL_Texture *border;
	SDL_Texture *snakeBody;
	SDL_Texture *snakeHeadDown;
	SDL_Texture *snakeHeadUp;
	SDL_Texture *snakeHeadLeft;
	SDL_Texture *snakeHeadRight;
	SDL_Texture *snakeTail;
	SDL_Texture *apple;
	SDL_Texture *banana;
	SDL_Texture *bomb;

	SDL_Event ev; // needed for closing the game window

	// corresponding to text
	SDL_Texture *text;
	SDL_Texture *playerNameText;
	SDL_Texture *scoreText;
	SDL_Texture *currentScore;

	// corresponding to music
	Mix_Music * backgroundMusic;
	Mix_Chunk * soundEffect1;
	Mix_Chunk * soundEffect2;
	Mix_Chunk * soundEffect3;

	
public:
	Graphics();
	~Graphics();

	void setConsole(int width, int height);

	void draw(int screenWidth, int screenHeight, Board *board);
	void drawName(const char* playerName);
	void drawScore(int score);

	void presentGraphics();
	void gameOverWindow(int score);
	void pauseWindow();

	void music();
	void playSoundEffect1();
	void playSoundEffect2();

	bool isWindowClosed();
	void haltMusic();
	void resumeMusic();
};

