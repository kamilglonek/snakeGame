#include "SnakePart.h"
#include <string>

SnakePart::SnakePart() {
}

SnakePart::~SnakePart() {

}

Field * SnakePart::getField() {
	return this->field;
}

void SnakePart::setField(Field * field) {
	if (this->field != NULL)
		this->field->setSnakePart(NULL);
	this->field = field;
	if (field != NULL)
		field->setSnakePart(this);
}
