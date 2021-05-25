#include "game.h"

int Game::Run()
{
	screen.Init("Super game", FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	actor.Init(&screen, 5);

	int keyPressed = 0;

	while (keyPressed != KEY_ESCAPE) {
		if (_kbhit()) {
			keyPressed = _getch();
	
			switch (keyPressed) {
			case KEY_ARROW_UP:
				if (!actor.CheckCollision(Actor::UP))
					actor.Move(Actor::UP);
				break;
			case KEY_ARROW_DOWN:
				if (!actor.CheckCollision(Actor::DOWN))
					actor.Move(Actor::DOWN);
				break;
			case KEY_ARROW_LEFT:
				if (!actor.CheckCollision(Actor::LEFT))
					actor.Move(Actor::LEFT);
				break;
			case KEY_ARROW_RIGHT:
				if (!actor.CheckCollision(Actor::RIGHT))
					actor.Move(Actor::RIGHT);
				break;
			}
		}
	}

	return 0;
}

