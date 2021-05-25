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
	COORD leftTop; // ��������� ������ �������� ����
	char c = char(177); //������ ���������
	char d = ' '; //������ ���������
	int size = 8; //������ � ������ ��������������
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
	SetConsoleTitle("Box moving!");// ����� ��������� ����
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	// ����������� ������ � ������ ����������� ����
	CONSOLE_SCREEN_BUFFER_INFO csbInfo;
	GetConsoleScreenBufferInfo(hStdOut, &csbInfo);
	WORD wOldColorAttrs;
	wOldColorAttrs = csbInfo.wAttributes;
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	COORD cursorPos = { 5, 2 }; // ��������� ���������� �������
	//������� ������ ��������������
	textRect rect(hStdOut, cursorPos);
	int iKey = 67;
	while (iKey != 27) // ����� �� ������� ESC
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
			case 120: //������� x
			case 88: //������� X
				exit(0); //���������� ���������
			}
		}
	}

	SetConsoleTextAttribute(hStdOut, wOldColorAttrs);

	return 0;
}

// ������ ��������������
void textRect::draw()
{
	COORD pos = leftTop;
	for (int j = 0; j < size; j++) {
		drawline(pos, VERT, c); //������ ������������ �����
		pos.X += 1;
	}
	// ��������� ������ � ������ �������
	SetConsoleCursorPosition(hStdOut, { 0,0 });
}
// �������������� ��������� �������������
void textRect::move(direction dir)
{
	COORD pos = leftTop;
	switch (dir)
	{
	case RIGHT:
		drawline(pos, VERT, d); //������� ����. �����
		pos = leftTop;
		pos.X += size;
		drawline(pos, VERT, c); //���������� ����. �����
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
		drawline(pos, HOR, d); //������� ���. �����
		pos = leftTop;
		pos.Y += size;
		drawline(pos, HOR, c); //���������� ���. �����
		leftTop.Y += 1;
		break;
	case UP:
		pos.Y += size - 1;
		drawline(pos, HOR, d); //������� ���. �����
		pos = leftTop;
		pos.Y -= 1;
		drawline(pos, HOR, c); //���������� ���. �����
		leftTop.Y -= 1;
		break;
	default:
		break;
	}
	// ��������� ������ � ������ �������
	SetConsoleCursorPosition(hStdOut, { 0,0 });
}
// ���� dir=VERT �������� ������������ ����� ��������� ch
// ����� �������� �������������� �����
void textRect::drawline(COORD cursorPos, style dir, char ch)
{
	for (int i = 0; i < size; i++) {
		SetConsoleCursorPosition(hStdOut, cursorPos);
		cout << ch;
		if (dir == VERT) cursorPos.Y += 1; else cursorPos.X += 1;
	}
}
