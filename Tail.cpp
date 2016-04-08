#include "Tail.h"

Tail::Tail() {
	this->field = NULL;
	this->shape = '+';
}

Tail::~Tail() {
}

char Tail::getShape() {
	return this->shape;
}

void Tail::setShape(char shape) {
}
