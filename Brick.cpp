#include "Brick.h"


Brick::Brick(int x, int y, int score):Item(x,y,50,20)
{
	PointValue = score;
}

Brick::Brick(int x, int y, int width, int height):Item(x,y,width,height)
{
	PointValue = 50;
}

Brick::Brick(int x, int y, BrickColor color):Item(x,y,width,height)
{
	PointValue = 50;
	RecoloreSprite(color);
}

int Brick::getScore()
{
	return PointValue;
}

Brick::~Brick(void)
{
}
