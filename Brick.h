#pragma once
#include "item.h"


class Brick :
	public Item
{

private:
	int PointValue;

public:
	Brick(int, int, int, int);
	Brick(int, int, int);

	Brick(int, int, BrickColor);

	int getScore();

	~Brick(void);
};

