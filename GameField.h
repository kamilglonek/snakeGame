#pragma once
#include "Field.h"
#include "Surprise.h"
#include "Apple.h"
#include "Banana.h"
#include "Bomb.h"

class GameField : public Field {
private:
	Surprise *surprise;
public:
	GameField();
	~GameField();

	Surprise *getSurprise();
	void setSurprise(int number);
	void removeSurprise();

	bool isBound();
	
	bool isSurprise();
	
};

