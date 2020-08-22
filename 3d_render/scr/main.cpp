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
	triangled tris[8];
	triangled tris1[8];

	tris[0].p1 = { -0.35,-0.25,-0.5 };
	tris[0].p2 = { 0.35,-0.25,-0.5 };
	tris[0].p3 = { 0.35,0.25,-0.5 };

	tris[1].p1 = { -0.35,-0.25,-0.5 };
	tris[1].p2 = { 0.35,0.25,-0.5 };
	tris[1].p3 = { -0.35,0.25,-0.5 };

	tris[2].p1 = { -0.35,-0.25,0.5 };
	tris[2].p2 = { -0.35,-0.25,-0.5 };
	tris[2].p3 = { -0.35,0.25,-0.5 };

	tris[3].p1 = { -0.35,-0.25,0.5 };
	tris[3].p2 = { -0.35,0.25,-0.5 };
	tris[3].p3 = { -0.35,0.25,0.5 };

	tris[4].p1 = { 0.35,-0.25,-0.5 };
	tris[4].p2 = { 0.35,-0.25,0.5 };
	tris[4].p3 = { 0.35,0.25,-0.5 };

	tris[5].p1 = { 0.35,0.25,-0.5 };
	tris[5].p2 = { 0.35,-0.25,0.5 };
	tris[5].p3 = { 0.35,0.25,0.5 };

	tris[6].p1 = { 0.35,-0.25,0.5 };
	tris[6].p2 = { -0.35,-0.25,0.5 };
	tris[6].p3 = { -0.35,0.25,0.5 };

	tris[7].p1 = { 0.35,-0.25,0.5 };
	tris[7].p2 = { -0.35,0.25,0.5 };
	tris[7].p3 = { 0.35,0.25,0.5 };


	

	FillConsole(buffer, WIDTH, HEIGHT);

	double angle = 0.0;


	while (true) {
		matrix_3x3 rot = Create_Simple_Rotation(angle, { 0,0,1 });

		for (int i = 0; i < 8; ++i) {
			tris1[i].p1 = rot * tris[i].p1;
			tris1[i].p2 = rot * tris[i].p2;
			tris1[i].p3 = rot * tris[i].p3;
		}
		Move_Mesh(tris1, 8, { 1.0,0.8,2.0 });

		for (int i = 0; i < 8; ++i) {
			DrawTriangle(tris1[i], buffer, WIDTH, HEIGHT, 90.0);
		}

		WriteConsoleOutputA(hwnd, buffer, { (short)WIDTH,(short)HEIGHT }, { 0,0 }, &m_react);
		FillConsole(buffer, WIDTH, HEIGHT);

		angle += 1;
	}

}