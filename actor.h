#pragma once

#include "screen.h"

class Actor
{
public:
	enum Direction { RIGHT, LEFT, UP, DOWN };

public:
	void Init(const char* name, int sz = 8, COORD Pos=COORD{ 0,0 })
	{
		size = sz;
		screen.Init(name, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		leftTop = Pos; 
		Draw();
	}

	void Draw();
	bool CheckCollision(Direction dir);
	void Move(Direction dir);
	short GetRight() { return leftTop.X + size; }
	short GetLeft() { return leftTop.X; }
	short GetTop() { return leftTop.Y; }
	short GetBottom() { return leftTop.Y + size; }

private:
	Screen screen;
	COORD leftTop{ 0,0 };		// положение левого верхнего угла
	char fillChar{ char(177) };	// символ рисования
	char delChar{ ' ' };		// символ затирания
	int size{ 8 };				// ширина и высота прямоугольника
};