#pragma once
#include "SnakePart.h"

class Body : public SnakePart {
private:
	char shape;
public:
	Body();
	~Body();

	char getShape();
	void setShape(char shape);
};

