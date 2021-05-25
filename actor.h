#pragma once

#include "screen.h"

class Actor
{
public:
	enum Direction { RIGHT, LEFT, UP, DOWN };

public:
	void Init(Screen* scr, int sz = 8, COORD Pos=COORD{ 0,0 })
	{
		screen = scr;
		size = sz;
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
	Screen* screen;
	COORD leftTop{ 0,0 };		// ��������� ������ �������� ����
	char fillChar{ char(177) };	// ������ ���������
	char delChar{ ' ' };		// ������ ���������
	int size{ 8 };				// ������ � ������ ��������������
};