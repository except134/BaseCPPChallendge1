#pragma once

#include <windows.h>
#include <iostream>
#include <conio.h>

class Screen
{
public:
	~Screen();

	void Init(const char* name, unsigned short color = 0);
	void SetCursorPos(int x, int y);
	void DrawVerticalLine(int x, int y, int length, char ch);
	void DrawHorizontalLine(int x, int y, int length, char ch);
	SMALL_RECT GetScreenSize() { return consoleBufferInfo.srWindow; }

private:
	HANDLE						stdOutput;
	CONSOLE_SCREEN_BUFFER_INFO	consoleBufferInfo;
	unsigned short				oldColors;
};