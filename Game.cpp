#include "Game.h"

Game::Game() {
	string playerName;
	cout << "Your name: ";
	cin >> playerName;

	this->player = new Player(playerName);
	this->board = new Board(boardWidth, boardHeight);
	this->graphics->setConsole(800, 700);
	this->graphics = new Graphics();
}


Game::~Game() {
	delete this->player;
	delete this->board;
	delete this->graphics;
}

void gotoxy(short int x, short int y) {
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void Game::play() {
	bool isGameOver = false;
	bool isBomb = false;
	bool isAppleEaten = true;
	bool isSurpriseEaten = false; // doda dopiero po pierwszych 50 odœwie¿eniach
	bool isAffected = false;
	int randomX = 4, randomY = 4, randomX2 = 4, randomY2 = 4, randomSurprise = 1, timeCounter = 0, roundTime = 100, surpriseTime = 50;
	Snake *snake = this->player->getSnake();
	snake->setupSnake(board, snake->getHeadX(), snake->getHeadY());
	char input;
	bool ifPause = false;
	bool isSurprise = true;
	int affectNumber = 0;
	//display loop

	this->graphics->music();

	

	do {
		if (isAffected) {
			Surprise *surprise = board->getField(snake->getHeadX(), snake->getHeadY())->getSurprise();
			if (snake->affect(surprise, affectNumber, isBomb, isAppleEaten, isSurpriseEaten)) {
				board->getField(snake->getHeadX(), snake->getHeadY())->removeSurprise();
			}
			isAffected = false;
		}

		// setting random surpise (Banana or Bomb) at random GameField
		if (timeCounter == surpriseTime) {
			if (board->getField(randomX2, randomY2)->isSurprise()) {
				board->getField(randomX2, randomY2)->removeSurprise();
			}

			do {
				srand(time(NULL));
				randomX2 = (rand() + 123) % 23 + 2; // ¿eby siê randomki ró¿ni³y bo inaczej siê nadpisuj¹, trzbea pomyœleæ czy mo¿na inaczej 
				randomY2 = (rand() + 243) % 23 + 2;
				randomSurprise = rand() % 2 + 1;
			} while (board->getField(randomX2, randomY2)->isSurprise() || !board->getField(randomX2, randomY2)->isEmpty()); // ma losowaæ dopóki JEST niespodzianka! lub pole nie jest empty
			board->getField(randomX2, randomY2)->setSurprise(randomSurprise);
			isSurpriseEaten = false;
			timeCounter = 0;
		}

		if (isAppleEaten) {
			do {
				srand(time(NULL));
				randomX = rand() % 23 + 2;
				randomY = rand() % 23 + 2;
			} while (!board->getField(randomX, randomY)->isEmpty());
			board->getField(randomX, randomY)->setSurprise(3);
			isAppleEaten = false;
		}

		timeCounter++;


		/*gotoxy(0, 0);
		cout << endl << "SCORE: " << player->getSnake()->getLength() << endl;
		board->display();*/


		//GUI DISPLAY
		this->graphics->draw(750, 950, this->board);
		this->graphics->drawName(player->getName().c_str());
		this->graphics->drawScore(player->getSnake()->getLength());
		this->graphics->presentGraphics();

		/// moving of snake
		if (_kbhit()) {
			input = _getch();
		if (input == 'p') {
				ifPause = true;
				this->graphics->pauseWindow();
				this->graphics->presentGraphics();
				this->graphics->haltMusic();
				do {
					if (_kbhit()) {
						input = _getch();
						if (input == 'p') {
							ifPause = false;
							this->graphics->resumeMusic();
						}
					}
				} while (ifPause);
			}
			snake->setDirection(input);
		}
		else {
			snake->setDirection(snake->getDirection());
		}


		/// checking if snake reached a surprise
		if (board->getField(snake->getHeadX(), snake->getHeadY())->isSurprise()) {
			isAffected = true;
			this->graphics->playSoundEffect1();
		}


		if (isGameOver = player->round(board) || isBomb) {
			this->graphics->playSoundEffect2();
			Mix_HaltMusic();
			Sleep(2000);
			this->graphics->gameOverWindow(this->player->getSnake()->getLength());
			while (!this->graphics->isWindowClosed()) { // we wait until user closes window

			}
		}
		Sleep(roundTime);
	} while (!isGameOver && !isBomb && !this->graphics->isWindowClosed());

}
