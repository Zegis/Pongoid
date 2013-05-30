#pragma once

#include<allegro5\allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include<allegro5/allegro_primitives.h>
#include<iostream>
#include"Item.h"
#include"Brick.h"
#include<list>
#include<sstream>

class Game
{

	private:

		ALLEGRO_DISPLAY * display;
		ALLEGRO_EVENT_QUEUE *queue;
		ALLEGRO_TIMER *timer;

		ALLEGRO_BITMAP *pong;
		ALLEGRO_BITMAP *ballSprite;
		ALLEGRO_BITMAP *brick[3];

		ALLEGRO_FONT *font;
		ALLEGRO_FONT *scoreFont;

		bool victory;
		bool running;
		bool pause;

		Item paddle;
		Item ball;

		int score;
		int hp;

		std::list<Brick> bricks;

		bool InitializeAllegro();
		bool PrepareSpritesAndFonts();

		void DeinitializeAllegro();
		void DestroySpritesAndFonts();

		void Draw();
		void DrawScene();
		void DrawEnd();

	public:

		Game(void);

		~Game(void);

		void GameLoop();

		bool Initialize();
		void Deinitialize();
		
};