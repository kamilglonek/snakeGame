#pragma once
#include "SnakePart.h"

class Tail : public SnakePart {
private:
	char shape;
public:
	Tail();
	~Tail();

	char getShape();
	void setShape(char shape);
};

