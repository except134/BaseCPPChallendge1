#include <windows.h>
#include <iostream>
#include <conio.h>

#include "game.h"

using namespace std;

#define KEY_ARROW_UP 72
#define KEY_ARROW_RIGHT 77
#define KEY_ARROW_DOWN 80
#define KEY_ARROW_LEFT 75
enum direction { RIGHT, LEFT, UP, DOWN };
class textRect {
	enum style { HOR, VERT };
	HANDLE hStdOut;
	COORD leftTop; // положение левого верхнего угла
	char c = char(177); //символ рисовани€
	char d = ' '; //символ затирани€
	int size = 8; //ширина и высота пр€моугольника
	void drawline(COORD cursorPos, style dir, char ch);
public:
	textRect(HANDLE hStdOut, COORD Pos)
	{
		this->hStdOut = hStdOut; leftTop = Pos; draw();
	}
	void draw();
	void move(direction dir);
	short right() { return leftTop.X + size; }
	short left() { return leftTop.X; }
	short top() { return leftTop.Y; }
	short bottom() { return leftTop.Y + size; }
};

int main()
{
	Game game;
	return game.Run();
}

int main2()
{
	SetConsoleTitle("Box moving!");// вывод заголовка окна
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	// определение ширины и высоты консольного окна
	CONSOLE_SCREEN_BUFFER_INFO csbInfo;
	GetConsoleScreenBufferInfo(hStdOut, &csbInfo);
	WORD wOldColorAttrs;
	wOldColorAttrs = csbInfo.wAttributes;
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	COORD cursorPos = { 5, 2 }; // положение текстового курсора
	//создаем объект пр€моугольника
	textRect rect(hStdOut, cursorPos);
	int iKey = 67;
	while (iKey != 27) // ¬ыход по клавише ESC
	{
		if (_kbhit())
		{
			iKey = _getch();
			switch (iKey)
			{
			case KEY_ARROW_UP:
				if (rect.top() <= csbInfo.srWindow.Top)
					cout << "\a";
				else rect.move(UP);
				break;
			case KEY_ARROW_RIGHT:
				if (rect.right() > csbInfo.srWindow.Right)
					cout << "\a";
				else rect.move(RIGHT);
				break;
			case KEY_ARROW_DOWN:
				if (rect.bottom() > csbInfo.srWindow.Bottom)
					cout << "\a";
				else rect.move(DOWN);
				break;
			case KEY_ARROW_LEFT:
				if (rect.left() <= csbInfo.srWindow.Left)
					cout << "\a";
				else rect.move(LEFT);
				break;
			case 120: //клавиша x
			case 88: //клавиша X
				exit(0); //завершение программы
			}
		}
	}

	SetConsoleTextAttribute(hStdOut, wOldColorAttrs);

	return 0;
}

// ѕечать пр€моугольника
void textRect::draw()
{
	COORD pos = leftTop;
	for (int j = 0; j < size; j++) {
		drawline(pos, VERT, c); //печать вертикальной линию
		pos.X += 1;
	}
	// “екстовый курсор в начало консоли
	SetConsoleCursorPosition(hStdOut, { 0,0 });
}
// перепечатываем сдвинутый пр€моугольник
void textRect::move(direction dir)
{
	COORD pos = leftTop;
	switch (dir)
	{
	case RIGHT:
		drawline(pos, VERT, d); //стереть верт. линию
		pos = leftTop;
		pos.X += size;
		drawline(pos, VERT, c); //напечатать верт. линию
		leftTop.X += 1;
		break;
	case LEFT:
		pos.X += size - 1;
		drawline(pos, VERT, d);
		pos = leftTop;
		pos.X -= 1;
		drawline(pos, VERT, c);
		leftTop.X -= 1;
		break;
	case DOWN:
		drawline(pos, HOR, d); //стереть гор. линию
		pos = leftTop;
		pos.Y += size;
		drawline(pos, HOR, c); //напечатать гор. линию
		leftTop.Y += 1;
		break;
	case UP:
		pos.Y += size - 1;
		drawline(pos, HOR, d); //стереть гор. линию
		pos = leftTop;
		pos.Y -= 1;
		drawline(pos, HOR, c); //напечатать гор. линию
		leftTop.Y -= 1;
		break;
	default:
		break;
	}
	// “екстовый курсор в начало консоли
	SetConsoleCursorPosition(hStdOut, { 0,0 });
}
// ≈сли dir=VERT печатаем вертикальную линию символами ch
// иначе печатаем горизонтальную линию
void textRect::drawline(COORD cursorPos, style dir, char ch)
{
	for (int i = 0; i < size; i++) {
		SetConsoleCursorPosition(hStdOut, cursorPos);
		cout << ch;
		if (dir == VERT) cursorPos.Y += 1; else cursorPos.X += 1;
	}
}
