#pragma once
#include <string>

using namespace std;

#include "SnakePart.h"
#include "Surprise.h"

class SnakePart;

class Field{
protected:
	SnakePart *snakePart;
public:
	Field();
	virtual ~Field();

	SnakePart *getSnakePart();
	void setSnakePart(SnakePart *snakePart);
	
	bool isEmpty();

	virtual bool isBound() = 0;
	virtual void removeSurprise() = 0;
	virtual Surprise *getSurprise() = 0;
	virtual void setSurprise(int number) = 0;

	virtual bool isSurprise() = 0;
	
};

