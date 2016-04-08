#include "Board.h"


Board::Board(int boardWidth, int boardHeight) {
	this->width = boardWidth;
	this->height = boardHeight;
	for (int i = 1; i <= boardWidth; i++) {
		for (int j = 1; j <= boardHeight; j++) {
			if (i == 1 || i == boardWidth || j == 1 || j == boardHeight) {
				fields.push_back(new Bound());
			}
			else {
				fields.push_back(new GameField());
			}
		}
	}
}

Board::~Board() {
	for (vector<class Field*>::iterator it = fields.begin(); it != fields.end(); ++it)
	{
		delete *it;
	}
	fields.clear();
}

Field * Board::getField(int x, int y) {
	return (&fields)->at(((y - 1) * 25) + (x - 1));
}

void Board::display() {
	int x = 0;
	vector<class Field *>::iterator iterator;
	for (iterator = fields.begin(); iterator != fields.end(); ++iterator) {
		if (x % 25 == 0) {
			cout << endl;
		}
		if ((*iterator)->isBound()) {
			cout << "X ";
		}
		else if (!(*iterator)->isBound() && !(*iterator)->isSurprise()) {
			if ((*iterator)->getSnakePart() == NULL) {
				cout << "  ";
			}
			else {
				cout << (*iterator)->getSnakePart()->getShape() << " ";
			}
		}
		else if (!(*iterator)->isBound() && (*iterator)->isSurprise()) {
			if ((*iterator)->getSnakePart() != NULL) {
				cout << (*iterator)->getSnakePart()->getShape() << " ";
			}
			else cout << (*iterator)->getSurprise()->getShape() << " ";
		}
		++x;
	}
}
