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

enum GameState
{
	Running,
	Defeat,
	Victory,
	Pause
};

class Game
{

	private:

		ALLEGRO_DISPLAY * display;
		ALLEGRO_EVENT_QUEUE *queue;
		ALLEGRO_TIMER *timer;

		ALLEGRO_BITMAP *pongSprite;
		ALLEGRO_BITMAP *ballSprite;
		ALLEGRO_BITMAP *brick[3];

		ALLEGRO_FONT *font;
		ALLEGRO_FONT *scoreFont;

		GameState gameState;

		Item paddle;
		Item ball;

		int score;
		int lives;

		std::list<Brick> bricks;

		bool InitializeAllegro();
		bool PrepareSpritesAndFonts();

		bool PrepareSprites();
		bool PrepareFonts();

		void DeinitializeAllegro();
		void DestroySpritesAndFonts();

		void DestroySprites();
		void DestroyFonts();

		void Draw();
		void DrawGui();
		void DrawScene();
		void DrawPause();
		void DrawEnd();

	public:

		Game(void);

		~Game(void);

		void GameLoop();

		bool Initialize();
		void Deinitialize();
		
};