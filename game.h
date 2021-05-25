#pragma once

#include "actor.h"

#define KEY_ESCAPE 27
#define KEY_ARROW_UP 72
#define KEY_ARROW_RIGHT 77
#define KEY_ARROW_DOWN 80
#define KEY_ARROW_LEFT 75

class Game
{
public:
	int Run();

private:
	Screen screen;
	Actor actor;
};
