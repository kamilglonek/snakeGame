#pragma once
#include "Field.h"

class Bound : public Field{
public:
	Bound();
	~Bound();

	bool isBound();

	bool isSurprise();

	void removeSurprise();
	Surprise *getSurprise();
	void setSurprise(int number);
};

