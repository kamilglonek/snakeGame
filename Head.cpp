#include "Head.h"

Head::Head() {
	this->field = NULL;
	this->shape = '>';
}


Head::~Head() {
}

char Head::getShape() {
	return this->shape;
}

void Head::setShape(char shape) {
	this->shape = shape;
}
