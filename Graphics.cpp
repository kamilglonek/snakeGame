#include "Graphics.h"

Graphics::Graphics() {
	this->window = NULL;
	this->backgroundImage = NULL;
	this->renderTarget = NULL;
	SDL_Init(SDL_INIT_VIDEO);

	SDL_GetCurrentDisplayMode(0, &DM);

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
		cout << "Error " << IMG_GetError() << endl;
	if (DM.h <= 900 || DM.w <= 750)
		this->window = SDL_CreateWindow("Snake Game vintage v.1.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH*0.8, SCREEN_HEIGHT*0.8, SDL_WINDOW_SHOWN);
	else
		this->window = SDL_CreateWindow("Snake Game vintage v.1.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	this->renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	this->backgroundImage = IMG_LoadTexture(renderTarget, "textures/pureBackground.png");
	this->border = IMG_LoadTexture(renderTarget, "textures/borderPattern.png");
	this->snakeBody = IMG_LoadTexture(renderTarget, "textures/body.png");
	this->snakeHeadDown = IMG_LoadTexture(renderTarget, "textures/headdown.png");
	this->snakeHeadUp = IMG_LoadTexture(renderTarget, "textures/headup.png");
	this->snakeHeadLeft = IMG_LoadTexture(renderTarget, "textures/headleft.png");
	this->snakeHeadRight = IMG_LoadTexture(renderTarget, "textures/headright.png");
	this->snakeTail = IMG_LoadTexture(renderTarget, "textures/tail.png");
	this->apple = IMG_LoadTexture(renderTarget, "textures/apple.png");
	this->banana = IMG_LoadTexture(renderTarget, "textures/banana.png");
	this->bomb = IMG_LoadTexture(renderTarget, "textures/bomb.png");


	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
		std::cout << "Error: " << Mix_GetError() << std::endl;
	}

	this->backgroundMusic = Mix_LoadMUS("sounds/music5.mp3");
	this->soundEffect1 = Mix_LoadWAV("sounds/Omnomnom.wav");
	this->soundEffect2 = Mix_LoadWAV("sounds/gameOver.wav");
	this->soundEffect3 = Mix_LoadWAV("sounds/cartoon.wav");
	

}

Graphics::~Graphics() {
	Mix_FreeMusic(backgroundMusic);
	Mix_FreeChunk(soundEffect1);
	Mix_FreeChunk(soundEffect2);
	this->backgroundMusic = NULL;
	this->soundEffect1 = NULL;
	this->soundEffect2 = NULL;


	SDL_DestroyWindow(window);
	SDL_DestroyTexture(backgroundImage);
	SDL_DestroyTexture(border);
	SDL_DestroyTexture(snakeBody);
	SDL_DestroyTexture(snakeHeadDown);
	SDL_DestroyTexture(snakeHeadLeft);
	SDL_DestroyTexture(snakeHeadRight);
	SDL_DestroyTexture(snakeHeadUp);
	SDL_DestroyTexture(snakeTail);
	SDL_DestroyTexture(apple);
	SDL_DestroyTexture(banana);
	SDL_DestroyTexture(bomb);
	SDL_DestroyTexture(text);
	SDL_DestroyTexture(playerNameText);
	SDL_DestroyTexture(scoreText);
	SDL_DestroyTexture(currentScore);
	SDL_DestroyRenderer(renderTarget);
	this->window = NULL;
	this->backgroundImage = NULL;
	this->border = NULL;
	this->snakeBody = NULL;
	this->snakeHeadDown = NULL;
	this->snakeHeadLeft = NULL;
	this->snakeHeadRight = NULL;
	this->snakeHeadUp = NULL;
	this->snakeTail = NULL;
	this->apple = NULL;
	this->banana = NULL;
	this->bomb = NULL;
	this->text = NULL;
	this->playerNameText = NULL;
	this->scoreText = NULL;
	this->currentScore = NULL;
	this->renderTarget = NULL;
	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Graphics::setConsole(int width, int height) {
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
	SetConsoleTitle(TEXT("Snake Game vintage v.1.0"));
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 10); // black background and green letters :)
}


void Graphics::music() {
	Mix_PlayMusic(backgroundMusic, -1);
}

void Graphics::playSoundEffect1() {
	Mix_PlayChannel(2, soundEffect1, 0);
}

void Graphics::playSoundEffect2() {
	Mix_PlayChannel(2, soundEffect2, 0);
}

bool Graphics::isWindowClosed() {
	while (SDL_PollEvent(&ev) != 0) {
		
		if (ev.type == SDL_QUIT) {
			return true;
		}
		else return false;
	}
}

void Graphics::haltMusic() {
	Mix_PauseMusic();
	Mix_PlayChannel(2, soundEffect3, 0);
}

void Graphics::resumeMusic() {
	Mix_ResumeMusic();
	Mix_PlayChannel(2, soundEffect3, 0);
}

void Graphics::draw(int screenWidth, int screenHeight, Board *board) {
	//DISPLAY
	SDL_RenderClear(renderTarget);
	SDL_RenderCopy(renderTarget, backgroundImage, NULL, NULL); // we draw the texture to the renderer

	int x = 0;
	int y = 200;
	int a = 0;
	SDL_Rect field{ x,y,30,30 };
	vector<class Field*>::iterator iterator;
	for (iterator = board->fields.begin(); iterator != board->fields.end(); iterator++) {
		if (a == 25) {
			field.y += 30;
			field.x = 0;
			a = 0;
		}
		if ((*iterator)->isBound()) {
			SDL_RenderCopy(renderTarget, border, NULL, &field);
		}
		else if (!(*iterator)->isBound() && !(*iterator)->isSurprise()) {
			if ((*iterator)->getSnakePart() != NULL) {
				if ((*iterator)->getSnakePart()->getShape() == '^') {
					SDL_RenderCopy(renderTarget, snakeHeadUp, NULL, &field);
				}
				else if ((*iterator)->getSnakePart()->getShape() == 'v') {
					SDL_RenderCopy(renderTarget, snakeHeadDown, NULL, &field);
				}
				else if ((*iterator)->getSnakePart()->getShape() == '<') {
					SDL_RenderCopy(renderTarget, snakeHeadLeft, NULL, &field);
				}
				else if ((*iterator)->getSnakePart()->getShape() == '>') {
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
				if ((*iterator)->getSnakePart()->getShape() == '^') {
					SDL_RenderCopy(renderTarget, snakeHeadUp, NULL, &field);
				}
				else if ((*iterator)->getSnakePart()->getShape() == 'v') {
					SDL_RenderCopy(renderTarget, snakeHeadDown, NULL, &field);
				}
				else if ((*iterator)->getSnakePart()->getShape() == '<') {
					SDL_RenderCopy(renderTarget, snakeHeadLeft, NULL, &field);
				}
				else if ((*iterator)->getSnakePart()->getShape() == '>') {
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
				if ((*iterator)->getSurprise()->getShape() == '@') {
					SDL_RenderCopy(renderTarget, apple, NULL, &field);
				}
				else if ((*iterator)->getSurprise()->getShape() == 'C') {
					SDL_RenderCopy(renderTarget, banana, NULL, &field);
				}
				else if ((*iterator)->getSurprise()->getShape() == 'Q') {
					SDL_RenderCopy(renderTarget, bomb, NULL, &field);
				}
			}
		}
		field.x += 30;
		a++;
	}
}

void Graphics::drawName(const char * playerName) {
	if (TTF_Init() < 0) {
		cout << "ERROR: " << TTF_GetError() << endl;
	}
	else {
		TTF_Font *font = TTF_OpenFont("Fonts/moon.ttf", 70);
		SDL_Color color = { 0,0,0,255 };
		SDL_Surface *textSurface = TTF_RenderText_Solid(font, "NAME:", color);
		SDL_Surface *playerNameSurface = TTF_RenderText_Solid(font, playerName, color);
		text = SDL_CreateTextureFromSurface(renderTarget, textSurface);
		playerNameText = SDL_CreateTextureFromSurface(renderTarget, playerNameSurface);
		//free surfaces
		SDL_FreeSurface(textSurface);
		SDL_FreeSurface(playerNameSurface);
		textSurface = NULL;
		playerNameSurface = NULL;
		// coming back
		SDL_Rect textRect, playerNameRect;
		textRect.x = 60;
		textRect.y = playerNameRect.y = 20;
		playerNameRect.x = 180;
		SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);
		SDL_QueryTexture(playerNameText, NULL, NULL, &playerNameRect.w, &playerNameRect.h);
		SDL_RenderCopy(renderTarget, text, NULL, &textRect);
		SDL_RenderCopy(renderTarget, playerNameText, NULL, &playerNameRect);
	}
}

void Graphics::drawScore(int score) {
	char scoreTab[4];
	_itoa_s(score, scoreTab, 10);
	TTF_Font *font = TTF_OpenFont("Fonts/moon.ttf", 70);
	SDL_Color color = { 0,0,0,255 };
	SDL_Surface *textSurface = TTF_RenderText_Solid(font, "SCORE:", color);
	SDL_Surface *scoreSurface = TTF_RenderText_Solid(font, scoreTab, color);
	scoreText = SDL_CreateTextureFromSurface(renderTarget, textSurface);
	currentScore = SDL_CreateTextureFromSurface(renderTarget, scoreSurface);
	// free unnecessary surfaces
	SDL_FreeSurface(textSurface);
	SDL_FreeSurface(scoreSurface);
	textSurface = NULL;
	scoreSurface = NULL;
	//come back to creating text
	SDL_Rect textRect, scoreRect;
	textRect.x = 60;
	textRect.y = scoreRect.y = 110;
	scoreRect.x = 180;
	SDL_QueryTexture(scoreText, NULL, NULL, &textRect.w, &textRect.h);
	SDL_QueryTexture(currentScore, NULL, NULL, &scoreRect.w, &scoreRect.h);
	SDL_RenderCopy(renderTarget, scoreText, NULL, &textRect);
	SDL_RenderCopy(renderTarget, currentScore, NULL, &scoreRect);
}

void Graphics::presentGraphics() {
	if (DM.h <= 900 || DM.w <= 750) SDL_RenderSetScale(renderTarget, 0.8, 0.8);
	SDL_RenderPresent(renderTarget); // Bo wystarczy raz :)
}

void Graphics::gameOverWindow(int score) {
	char scoreTab[4];
	_itoa_s(score, scoreTab, 10);

	SDL_RenderClear(renderTarget);
	SDL_RenderCopy(renderTarget, backgroundImage, NULL, NULL);

	TTF_Font *font = TTF_OpenFont("Fonts/moon.ttf", 110);
	TTF_Font *scoreFont = TTF_OpenFont("Fonts/moon.ttf", 700);
	SDL_Color color = { 0,0,0,255 };
	SDL_Color red = { 255,0,0,255 };
	SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Thanks for playing!", color);
	SDL_Surface *scoreSurface = TTF_RenderText_Solid(font, "is your final score!", color);
	SDL_Surface *scoredPoints = TTF_RenderText_Solid(scoreFont, scoreTab, red);

	SDL_Texture* thanksForPlaying = SDL_CreateTextureFromSurface(renderTarget, textSurface);
	SDL_Texture *youScored = SDL_CreateTextureFromSurface(renderTarget, scoreSurface);
	SDL_Texture *finalScore = SDL_CreateTextureFromSurface(renderTarget, scoredPoints);
	

	SDL_FreeSurface(textSurface);
	SDL_FreeSurface(scoreSurface);
	SDL_FreeSurface(scoredPoints);

	textSurface = NULL;
	scoreSurface = NULL;
	scoredPoints = NULL;


	SDL_Rect textRect, scoreRect, pointsRect;
	textRect.x = 70;
	textRect.y = 80;
	scoreRect.y = 770;
	scoreRect.x = 65;
	pointsRect.y = 130;
	if (scoreTab[1] == NULL) //change of the position of displayed points
		pointsRect.x = 250;
	else {
		if (scoreTab[2] == NULL) {
			pointsRect.x = 160;
		}
		else  pointsRect.x = 40;
	}


	SDL_QueryTexture(thanksForPlaying, NULL, NULL, &textRect.w, &textRect.h);
	SDL_QueryTexture(youScored, NULL, NULL, &scoreRect.w, &scoreRect.h);
	SDL_QueryTexture(finalScore, NULL, NULL, &pointsRect.w, &pointsRect.h);

	SDL_RenderCopy(renderTarget, thanksForPlaying, NULL, &textRect);
	SDL_RenderCopy(renderTarget, youScored, NULL, &scoreRect);
	SDL_RenderCopy(renderTarget, finalScore, NULL, &pointsRect);

	if (DM.h <= 900 || DM.w <= 750) SDL_RenderSetScale(renderTarget, 0.8, 0.8);
	SDL_RenderPresent(renderTarget);

	SDL_DestroyTexture(thanksForPlaying);
	SDL_DestroyTexture(youScored);
	SDL_DestroyTexture(finalScore);
	thanksForPlaying = NULL;
	youScored = NULL;
	finalScore = NULL;
}

void Graphics::pauseWindow() {
	TTF_Font *font = TTF_OpenFont("Fonts/moon.ttf", 70);
	SDL_Color color = { 255,0,0,255 };
	SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Paused", color);
	text = SDL_CreateTextureFromSurface(renderTarget, textSurface);
	//free surfaces
	SDL_FreeSurface(textSurface);
	textSurface = NULL;
	// coming back
	SDL_Rect textRect;
	textRect.x = 300;
	textRect.y = 430;
	SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);
	SDL_RenderCopy(renderTarget, text, NULL, &textRect);
}


