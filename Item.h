#pragma once
#include<allegro5\allegro5.h>

enum BrickColor
{
	Red,
	Green,
	Blue
};

class Item
{
public:

	int x;
	int y;

	int height;
	int width;

	int dx;
	int dy;

	ALLEGRO_BITMAP *sprite;

	Item(void);
	Item(int, int, int, int);

	void setItemSprite(ALLEGRO_BITMAP *);
	ALLEGRO_BITMAP* getItemSprite();

	~Item(void);

	void Move();

	void Rethrow(int, int);

	void Boundaries();

	void HorizontalBounce();
	void VerticalBounce();

	bool Collision(Item);

	void RecoloreSprite(BrickColor);

};