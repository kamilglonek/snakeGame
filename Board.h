#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "Field.h"
#include "Bound.h"
#include "GameField.h"

using namespace std;

class Board{
	friend class Graphics;
private:
	int width;
	int height;
	vector<class Field *> fields;
public:
	Board(int boardWidth, int boardHeight);
	~Board();

	Field *getField(int x, int y);

	void display();
};

