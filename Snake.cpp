#include "Snake.h"

Snake::Snake() {
	this->headX = 10;
	this->headY = 15;
	this->direction = RIGHT;
}

Snake::~Snake() {
}

SnakePart * Snake::getBody(int position) {
	return (&body)->at(position);;
}

void Snake::setupSnake(Board *board, int headX, int headY) {
	body.push_back(new Head());
	body.push_back(new Body());
	body.push_back(new Tail());

	this->length = body.size() - 2; // only main body counts, we do not take into account a head and a tail

	int counter;
	deque<class SnakePart *>::iterator iterator;
	for (iterator = body.begin(), counter = 0; iterator != body.end(); ++iterator, ++counter) {
		(*iterator)->setField(board->getField(headX - counter, headY));
	}
}

void Snake::move(Field * field) {

	deque<class SnakePart *>::iterator mover;
	Field *head = 0;
	Field *tmp;

	mover = body.begin();
	head = (*mover)->getField();
	(*mover)->setField(field);

	for (++mover; mover != body.end(); ++mover) {
		tmp = (*mover)->getField();
		(*mover)->setField(head);
		head = tmp;
	}
}

Direction Snake::getDirection() {
	return this->direction;
}

void Snake::setDirection(char inputKey) {
	switch (inputKey) {
	case 'w': if (getDirection() != DOWN) direction = UP; break;
	case 's': if (getDirection() != UP) direction = DOWN; break;
	case 'a': if (getDirection() != RIGHT) direction = LEFT; break;
	case 'd': if (getDirection() != LEFT) direction = RIGHT; break;
	}

	switch (direction) {
	case UP: --headY; this->getBody(0)->setShape('^'); break;
	case DOWN: ++headY; this->getBody(0)->setShape('v'); break;
	case LEFT: --headX; this->getBody(0)->setShape('<'); break;
	case RIGHT: ++headX; this->getBody(0)->setShape('>'); break;
	}
}

int Snake::getHeadX() {
	return headX;
}

void Snake::setheadX(int headX) {
	this->headX = headX;
}

int Snake::getHeadY() {
	return headY;
}

void Snake::setHeadY(int headY) {
	this->headY = headY;
}

int Snake::getLength() {
	return this->length;
}

void Snake::lengthen(int amount) {
	for (int i = 0; i < amount; i++) {
		deque<class SnakePart*>::iterator iterator = body.end() - 1;
		body.insert(iterator, new Body());
	}
}

//bool Snake::affect(Snake *snake, string type) {
//	if (type == "Apple") {
//		int affectNumber = 1;
//		snake->lengthen(affectNumber);
//		this->length = this->length + affectNumber;
//		return false;
//	}
//	else if (type == "Banana") {
//		int affectNumber = 2;
//		snake->lengthen(affectNumber);
//		this->length = this->length + affectNumber;
//		return false;
//	}
//	else if (type == "Bomb") {
//		return true;
//	}
//}

bool Snake::affect(Surprise * surprise, int &affectNumber, bool &isBomb,  bool &isAppleEaten, bool &isSurpriseEaten) {
	if (!surprise)
		return false;
	surprise->getEffects(affectNumber, isBomb, isAppleEaten, isSurpriseEaten);
	if (affectNumber > 0) {
		this->lengthen(affectNumber);
		this->length = this->length + affectNumber;
	}
}
