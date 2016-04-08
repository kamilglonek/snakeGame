#pragma once
#include "SnakePart.h"

class Head : public SnakePart {
private:
	char shape;
public:
	Head();
	~Head();

	char getShape();
	void setShape(char shape);
};

