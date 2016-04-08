#include "Body.h"

Body::Body() {
	this->field = NULL;
	this->shape = 'o';
}

Body::~Body() {
}

char Body::getShape() {
	return this->shape;
}

void Body::setShape(char shape) {
}
