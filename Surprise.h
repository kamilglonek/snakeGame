#pragma once
#include <string>
//#include "Snake.h" // do not include it bo sie wysypuje
//#include "Player.h" // the same

using namespace std;


class Surprise {
private:
	char shape;
public:
	Surprise();
	virtual ~Surprise();

	virtual char getShape() = 0;

	virtual void getEffects(int &affectNumber, bool &isBomb, bool &isAppleEaten, bool &isSurpriseEaten) = 0;

	virtual bool isNormalSurprise() = 0;
};

