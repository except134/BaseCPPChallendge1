#include "Screen.h"

Screen::~Screen()
{
	SetConsoleTextAttribute(stdOutput, oldColors);
}

void Screen::Init(const char* name, unsigned short color)
{
	SetConsoleTitle(name);
	stdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(stdOutput, &consoleBufferInfo);
	oldColors = consoleBufferInfo.wAttributes;
	if(color)
		SetConsoleTextAttribute(stdOutput, color);
}

void Screen::SetCursorPos(int x, int y)
{
	SetConsoleCursorPosition(stdOutput, { (short)x, (short)y });
}

void Screen::DrawVerticalLine(int x, int y, int length, char ch)
{
	for (int i = 0; i < length; i++) {
		SetCursorPos(x, y);
		std::cout << ch;
		y += 1; 
	}
}

void Screen::DrawHorizontalLine(int x, int y, int length, char ch)
{
	for (int i = 0; i < length; i++) {
		SetCursorPos(x, y);
		std::cout << ch;
		x += 1;
	}
}

