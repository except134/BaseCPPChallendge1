#include "actor.h"

void Actor::Draw()
{
	COORD pos = leftTop;
	for (int j = 0; j < size; j++) {
		screen->DrawVerticalLine(pos.X, pos.Y, size, fillChar); 
		pos.X += 1;
	}
	screen->SetCursorPos(0, 0);
}

bool Actor::CheckCollision(Direction dir)
{
	switch (dir) {
	case RIGHT:
		if (GetRight() > screen->GetScreenSize().Right)
			return true;
		break;
	case LEFT:
		if (GetLeft() <= screen->GetScreenSize().Left)
			return true;
		break;
	case DOWN:
		if (GetBottom() > screen->GetScreenSize().Bottom)
			return true;
		break;
	case UP:
		if (GetTop() <= screen->GetScreenSize().Top)
			return true;
		break;
	}
	return false;
}

void Actor::Move(Direction dir)
{
	COORD pos = leftTop;
	switch (dir) {
	case RIGHT:
		screen->DrawVerticalLine(pos.X, pos.Y, size, delChar); 
		pos = leftTop;
		pos.X += size;
		screen->DrawVerticalLine(pos.X, pos.Y, size, fillChar); 
		leftTop.X += 1;
		break;
	case LEFT:
		pos.X += size - 1;
		screen->DrawVerticalLine(pos.X, pos.Y, size, delChar); 
		pos = leftTop;
		pos.X -= 1;
		screen->DrawVerticalLine(pos.X, pos.Y, size, fillChar);
		leftTop.X -= 1;
		break;
	case DOWN:
		screen->DrawHorizontalLine(pos.X, pos.Y, size, delChar);
		pos = leftTop;
		pos.Y += size;
		screen->DrawHorizontalLine(pos.X, pos.Y, size, fillChar);
		leftTop.Y += 1;
		break;
	case UP:
		pos.Y += size - 1;
		screen->DrawHorizontalLine(pos.X, pos.Y, size, delChar);
		pos = leftTop;
		pos.Y -= 1;
		screen->DrawHorizontalLine(pos.X, pos.Y, size, fillChar);
		leftTop.Y -= 1;
		break;
	}
	screen->SetCursorPos(0, 0);
}
