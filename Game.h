#include "Player.h"
#include "Board.h"
#include "Graphics.h"
#include <string>
#include <iostream>
#include <windows.h>
#include <ctime>
#include <conio.h>

using namespace std;

const int boardWidth = 25;
const int boardHeight = 25;

class Game{
private:
	Player *player;
	Board *board;
	Graphics *graphics;
public:
	Game();
	~Game();
	void play();
};

