#pragma once
#include "item.h"


class Brick :
	public Item
{

private:
	int PointValue;

public:
	Brick(int x, int y, int width, int height);
	Brick(int x, int y, int score);

	Brick(int x, int y, BrickColor);

	int getScore();

	~Brick(void);
};

