#include "game.h"

int main()
{
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);

	int x = 0;
	for (float i = 0; i < 3.14 * 10; i += 0.05)
	{
		SetPixel(hdc, x, 50 + 25 * cos(i), RGB(255, 255, 255));
		x += 1;
	}

	ReleaseDC(hwnd, hdc);
	std::cin.ignore();
	return 0;

	Game game;
	return game.Run();
}

