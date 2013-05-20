#include "Item.h"

Item::Item(void)
{
}

Item::Item(int Xwsp, int Ywsp, int newWidth, int newHeight)
{
	x = Xwsp;
	y = Ywsp;

	dx = 4;
	dy = -4;

	width = newWidth;
	height = newHeight;
}

void Item::setItemSprite(ALLEGRO_BITMAP *newSprite)
{
	sprite = newSprite;
}

ALLEGRO_BITMAP* Item::getItemSprite()
{
	return sprite;
}

Item::~Item()
{
}

bool Item::Collision(Item itemToCheck)
{
	if(x > itemToCheck.x && x <= itemToCheck.x + itemToCheck.width && y <= itemToCheck.y+itemToCheck.height && y >= itemToCheck.y) return true;
	else if(x+width > itemToCheck.x && x+width <=itemToCheck.x+ itemToCheck.width && y <= itemToCheck.y+itemToCheck.height && y >= itemToCheck.y) return true;
	else if(x > itemToCheck.x && x <= itemToCheck.x + itemToCheck.width && y+height <= itemToCheck.y+itemToCheck.height && y+height >= itemToCheck.y) return true;
	else if(x+width > itemToCheck.x && x+width <= itemToCheck.x + itemToCheck.width && y+height <= itemToCheck.y+itemToCheck.height && y+height >= itemToCheck.y) return true;

	return false;
	
}

void Item::Move()
{
	Boundaries();
	x -= dx;
	y -= dy;
}

void Item::Boundaries()
{
	if(x < 0 || x > 768)
		HorizontalBounce();
	if(y == 0)
		VerticalBounce();
}

void Item::HorizontalBounce()
{
	dx = -dx;
}

void Item::VerticalBounce()
{
	dy = -dy;
}

void Item::Rethrow(int newX, int newY)
{
	x = newX;
	y = newY;
}

void Item::RecoloreSprite(BrickColor color)
{
	al_set_target_bitmap(sprite);

	if(color == BrickColor::Blue)
		al_clear_to_color(al_map_rgb(0,0,255));
	else if(color == BrickColor::Red)
		al_clear_to_color(al_map_rgb(255,0,0));
	else if(color == BrickColor::Green)
		al_clear_to_color(al_map_rgb(0,255,0));
	else
		al_clear_to_color(al_map_rgb(255,250,100));
}