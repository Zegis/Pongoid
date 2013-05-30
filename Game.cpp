#include "Game.h"

using namespace std;


Game::Game(void)
{
}

Game::~Game(void)
{
}

bool Game::Initialize()
{
	paddle = Item(400,564,100,32);
	ball = Item(400,300,20,20);

	if(InitializeAllegro())
		if(PrepareSpritesAndFonts())
		{
			running = true;
			hp = 3;
			pause = false;
			return true;
		}
		else
			DeinitializeAllegro();

	return false;
}

bool Game::InitializeAllegro()
{
	if(!al_init())
	{
		cout << "Allegro initialization failed!";
		cin.get();
		return false;
	}
	
	if(!al_install_keyboard())
	{
		cout << "Keyboard installation failed!";
		cin.get();
		return false;
	}

	timer = al_create_timer(1.0 / 50);

	if(!timer)
	{
		cout << "Failed to create a timer!";
		cin.get();

		al_uninstall_keyboard();
		return false;
	}
	
	display = al_create_display(800,600);
	if(!display)
	{
		cout << "Failed to create display!";
		cin.get();

		al_uninstall_keyboard();
		al_destroy_timer(timer);
		return false;
	}
	queue = al_create_event_queue();
	
	if(!queue)
	{
		cout << "Failed to create an event queue!";
		cin.get();

		al_uninstall_keyboard();
		al_destroy_timer(timer);
		al_destroy_display(display);
		return false;
	}

	al_register_event_source(queue,al_get_keyboard_event_source());
	al_register_event_source(queue,al_get_timer_event_source(timer));

	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();

	return true;
}

bool Game::PrepareSpritesAndFonts()
{
	ballSprite = al_create_bitmap(20,20);

	if(!ballSprite)
	{
		cout << "Failed to create sprite for the ball!";
		cin.get();
		return false;
	}

	al_set_target_bitmap(ballSprite);
	al_draw_filled_circle(10,10,9,al_map_rgb(255,255,255));

	pong = al_create_bitmap(100,32);

	if(!pong)
	{
		cout << "Failed to create sprite for paddle!";
		cin.get();

		al_destroy_bitmap(ballSprite);
		return false;
	}

	al_set_target_bitmap(pong);
	al_clear_to_color(al_map_rgb(0,255,0));

	for(int i=0; i<3; ++i)
	{
		brick[i] = al_create_bitmap(50,20);
		if(!brick[i])
		{
			cout << "Failed to create sprite for brick!";
			cin.get();
			al_destroy_bitmap(ballSprite);
			al_destroy_bitmap(pong);
			return false;
		}

		al_set_target_bitmap(brick[i]);
		al_clear_to_color(al_map_rgb(0,0,255));
	}

	al_set_target_bitmap(brick[0]);
		al_clear_to_color(al_map_rgb(255,0,255));

	al_set_target_bitmap(al_get_backbuffer(display));

	font = al_load_ttf_font("pirulen.ttf",52,0);

	if(!font)
	{
		cout << "Failed to create sprite for brick!";
		cin.get();
		al_destroy_bitmap(ballSprite);
		al_destroy_bitmap(pong);
		al_destroy_bitmap(brick[0]);
		al_destroy_bitmap(brick[1]);
		al_destroy_bitmap(brick[2]);
		return false;
	}

	scoreFont = al_load_ttf_font("pirulen.ttf",22,0);

	if(!scoreFont)
	{
		cout << "Failed to create sprite for brick!";
		cin.get();
		al_destroy_bitmap(ballSprite);
		al_destroy_bitmap(pong);
		al_destroy_bitmap(brick[0]);
		al_destroy_bitmap(brick[1]);
		al_destroy_bitmap(brick[2]);
		al_destroy_font(font);
		return false;
	}

	return true;
}

void Game::Deinitialize()
{
	DeinitializeAllegro();
	DestroySpritesAndFonts();
}

void Game::DeinitializeAllegro()
{
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);

	al_uninstall_keyboard();
}

void Game::DestroySpritesAndFonts()
{
	al_destroy_bitmap(pong);
	al_destroy_bitmap(ballSprite);
		al_destroy_bitmap(brick[0]);
		al_destroy_bitmap(brick[1]);
		al_destroy_bitmap(brick[2]);

	al_destroy_font(font);
	al_destroy_font(scoreFont);
}

void Game::GameLoop()
{
		bool redraw = false;
		
		ALLEGRO_EVENT ev;

		victory = false;
		score = 0;

		paddle.setItemSprite(pong);
		ball.setItemSprite(ballSprite);

		bool left = false, right = false;

		for(int i=0; i<12; ++i)
			for(int j=0; j<8; ++j)
			{
				Brick tmp(15 + i*54, 4+j*22,50,20);
				if (j != 7)
					tmp.setItemSprite(brick[1]);
				else
					tmp.setItemSprite(brick[0]);
				bricks.push_back(tmp);
			}

		al_set_target_bitmap(al_get_backbuffer(display));
		DrawScene();

		al_start_timer(timer);


		while(running)
		{
			al_wait_for_event(queue,&ev);

			if(ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_P)
			{
				pause = !pause;
				redraw = true;
			}

			if(ev.type == ALLEGRO_EVENT_KEY_CHAR && ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				running = false;

			if(pause && redraw == false)
				continue;

			if(ev.type == ALLEGRO_EVENT_TIMER)
			{
				if(right)
					paddle.x += (paddle.x < 700) ? 5 : 0;
				else if(left)
					paddle.x -= (paddle.x > 0) ? 5 : 0;

				ball.Move();

				if(ball.Collision(paddle))
				{
						ball.VerticalBounce();
				}

				for(list<Brick>::iterator it = bricks.begin(); it != bricks.end(); ++it)
				{
					if(ball.Collision(*it))
					{
						ball.VerticalBounce();
					
						score+=it->getScore();
						bricks.erase(it);
						break;
					}
				}

				if(bricks.size() == 0)
				{
					running = false;
					victory = true;
				}

				if(ball.y > 600)
				{
					ball.Rethrow(400,300);
					paddle.x = 400;
					if(--hp <= 0)
						running = false;
				}

				redraw = true;
			}
			
			if(ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_RIGHT)
				right = true;
			else if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_LEFT)
				left = true;

			if(ev.type == ALLEGRO_EVENT_KEY_UP && ev.keyboard.keycode == ALLEGRO_KEY_RIGHT)
				right = false;
			else if (ev.type == ALLEGRO_EVENT_KEY_UP && ev.keyboard.keycode == ALLEGRO_KEY_LEFT)
				left = false;
	
			if(redraw)
			{
				Draw();
				redraw = false;
			}
		}

		Draw();
		al_rest(2);
}

void Game::Draw()
{
	if (running == true) DrawScene();
	if (running == false) DrawEnd();
}

void Game::DrawScene()
{
	al_clear_to_color(al_map_rgb(0,0,0));

	al_draw_bitmap(ball.getItemSprite(),ball.x,ball.y,0);
	al_draw_bitmap(paddle.getItemSprite(),paddle.x,paddle.y,0);

	stringstream str;
	str << score;
	
	string scoreText = str.str();

	al_draw_text(scoreFont,al_map_rgb(255,255,255),750, 0, ALLEGRO_ALIGN_RIGHT, str.str().c_str());
	for(int i=hp; i > 1; --i)
		al_draw_scaled_bitmap(paddle.getItemSprite(),0,0,al_get_bitmap_width(paddle.getItemSprite()),al_get_bitmap_height(paddle.getItemSprite()),750,20+i*10,al_get_bitmap_width(paddle.getItemSprite()) * 0.25, al_get_bitmap_height(paddle.getItemSprite()) * 0.25 ,0);

	list<Brick>::iterator it;

	for(it = bricks.begin(); it!=bricks.end(); ++it)
		al_draw_bitmap(it->getItemSprite(),it->x,it->y,0);

	if(pause)
		al_draw_text(font,al_map_rgb(255,255,255),540, 250, ALLEGRO_ALIGN_RIGHT, "PAUSED!");

	al_flip_display();

}

void Game::DrawEnd()
{
	if(victory)
		al_draw_text(font,al_map_rgb(255,255,255),500, 250, ALLEGRO_ALIGN_RIGHT, "Victory!");
	else if(hp == 0)
		al_draw_text(font,al_map_rgb(255,255,255),525, 250, ALLEGRO_ALIGN_RIGHT, "Defeat!");

	al_flip_display();
}

