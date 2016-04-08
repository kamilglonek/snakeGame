#include "Draw.h"



Draw::Draw()
{
	window = NULL;
	backgroundImage = NULL;
	renderTarget = NULL;
	SDL_Init(SDL_INIT_VIDEO);

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
		cout << "Error " << IMG_GetError() << endl;

	window = SDL_CreateWindow("GameWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	backgroundImage = IMG_LoadTexture(renderTarget, "Textures/pureBackground.png");
	texture = IMG_LoadTexture(renderTarget, "Textures/borderPattern.png");
	snakeBody = IMG_LoadTexture(renderTarget, "Textures/body.png");
	snakeHeadDown = IMG_LoadTexture(renderTarget, "Textures/headdown.png");
	snakeHeadUp = IMG_LoadTexture(renderTarget, "Textures/headup.png");
	snakeHeadLeft = IMG_LoadTexture(renderTarget, "Textures/headleft.png");
	snakeHeadRight = IMG_LoadTexture(renderTarget, "Textures/headright.png");
	snakeTail = IMG_LoadTexture(renderTarget, "Textures/tail.png");
	apple = IMG_LoadTexture(renderTarget, "Textures/apple.png");
	banana = IMG_LoadTexture(renderTarget, "Textures/banana.png");
	bomb = IMG_LoadTexture(renderTarget, "Textures/bomb.png");




}


Draw::~Draw()
{
}

void Draw::setConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
	SetConsoleTitle(TEXT("SnakeGame"));
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 10); // black background and green letters :)
}


void Draw::setBackground(int width, int height, Board *board)
{
	//DISPLAY
	SDL_RenderClear(renderTarget);
	SDL_RenderCopy(renderTarget, backgroundImage, NULL, NULL); // we draw the texture to the renderer

	int x = 0;
	int y = 200;
	int a = 0;

	SDL_Rect field{ x,y,30,30 };
	for (iterator = board->fields.begin(); iterator != board->fields.end(); iterator++) {
		if (a == 25) {
			field.y += 30;
			field.x = 0;
			a = 0;
		}
		if ((*iterator)->isBound()) {
			SDL_RenderCopy(renderTarget, texture, NULL, &field);
		}
		else if (!(*iterator)->isBound() && !(*iterator)->isSurprise()) {
			if ((*iterator)->getSnakePart() != NULL) {
				if ((*iterator)->getSnakePart()->getShape() == '1') {
					SDL_RenderCopy(renderTarget, snakeHeadUp, NULL, &field);
				}
				else if ((*iterator)->getSnakePart()->getShape() == '2') {
					SDL_RenderCopy(renderTarget, snakeHeadDown, NULL, &field);
				}
				else if ((*iterator)->getSnakePart()->getShape() == '3') {
					SDL_RenderCopy(renderTarget, snakeHeadLeft, NULL, &field);
				}
				else if ((*iterator)->getSnakePart()->getShape() == '4') {
					SDL_RenderCopy(renderTarget, snakeHeadRight, NULL, &field);
				}
				else if ((*iterator)->getSnakePart()->getShape() == 'o') {
					SDL_RenderCopy(renderTarget, snakeBody, NULL, &field);
				}
				else if ((*iterator)->getSnakePart()->getShape() == '+') {
					SDL_RenderCopy(renderTarget, snakeTail, NULL, &field);
				}

			}
		}
		else if (!(*iterator)->isBound() && (*iterator)->isSurprise()) {
			if ((*iterator)->getSnakePart() != NULL) {
				if ((*iterator)->getSnakePart()->getShape() == '1') {
					SDL_RenderCopy(renderTarget, snakeHeadUp, NULL, &field);
				}
				else if ((*iterator)->getSnakePart()->getShape() == '2') {
					SDL_RenderCopy(renderTarget, snakeHeadDown, NULL, &field);
				}
				else if ((*iterator)->getSnakePart()->getShape() == '3') {
					SDL_RenderCopy(renderTarget, snakeHeadLeft, NULL, &field);
				}
				else if ((*iterator)->getSnakePart()->getShape() == '4') {
					SDL_RenderCopy(renderTarget, snakeHeadRight, NULL, &field);
				}
				else if ((*iterator)->getSnakePart()->getShape() == 'o') {
					SDL_RenderCopy(renderTarget, snakeBody, NULL, &field);
				}
				else if ((*iterator)->getSnakePart()->getShape() == '+') {
					SDL_RenderCopy(renderTarget, snakeTail, NULL, &field);
				}
			}
			else {
				if ((*iterator)->getSurprise()->getType() == "Apple") {
					SDL_RenderCopy(renderTarget, apple, NULL, &field);
				}
				else if ((*iterator)->getSurprise()->getType() == "Banana") {
					SDL_RenderCopy(renderTarget, banana, NULL, &field);
				}
				else if ((*iterator)->getSurprise()->getType() == "Bomb") {
					SDL_RenderCopy(renderTarget, bomb, NULL, &field);
				}
			}
		}


		field.x += 30;
		a++;
	}


	SDL_RenderPresent(renderTarget); // present the renderer on the screen

	//trzeba czyszczenie zrobiæ
}



