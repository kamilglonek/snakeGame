#pragma once
#include "Field.h"

class Field;

class SnakePart {
private:
	char shape;
protected:
	Field *field;
public:
	SnakePart();
	virtual ~SnakePart();

	virtual char getShape() = 0;
	virtual void setShape(char shape) = 0;

	Field *getField();
	void setField(Field *field);
};

