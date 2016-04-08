#include "Field.h"

Field::Field() {
	this->snakePart = NULL;
}


Field::~Field(){
	delete this->snakePart;
}

SnakePart * Field::getSnakePart() {
	return this->snakePart;
}

void Field::setSnakePart(SnakePart * snakePart) {
	this->snakePart = snakePart;
}

bool Field::isEmpty() {
	if (snakePart != NULL) return false;
	else return true;
}




