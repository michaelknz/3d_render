#include "render.h"

int WIDTH = 400;
int HEIGHT = 300;

int main() {
	HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
	HWND hwnd1;
	
	COORD size;
	size.X = WIDTH;
	size.Y = HEIGHT;
	SMALL_RECT m_react = { 0,0,1,1 };

	SetConsoleWindowInfo(hwnd, TRUE, &m_react);
	CONSOLE_FONT_INFOEX font = {};
	GetCurrentConsoleFontEx(hwnd, false, &font);
	font.dwFontSize = { 2,2 };
	font.cbSize = sizeof(font);
	lstrcpyW(font.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(hwnd, false, &font);

	SetConsoleScreenBufferSize(hwnd, size);
	m_react = { 0,0,(short)WIDTH - 1,(short)HEIGHT - 1 };
	SetConsoleWindowInfo(hwnd, TRUE, &m_react);

	CHAR_INFO* buffer = new CHAR_INFO[WIDTH * HEIGHT];
	triangled tri;
	tri.p1.x = 0.5;
	tri.p1.y = 0.5;
	tri.p1.z = 1;
	tri.p2.x = 0.25;
	tri.p2.y = 0.25;
	tri.p2.z = 1;
	tri.p3.x = 0.75;
	tri.p3.y = 0.25;
	tri.p3.z = 2;

	FillConsole(buffer, WIDTH, HEIGHT);
	DrawTriangle(tri, buffer, WIDTH, HEIGHT, 90.0);

	while (true) {
		WriteConsoleOutputA(hwnd, buffer, { (short)WIDTH,(short)HEIGHT }, { 0,0 }, &m_react);
	}

}