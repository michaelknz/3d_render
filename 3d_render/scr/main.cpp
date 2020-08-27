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
	triangle4d tris[8];
	triangle4d tris1[8];

	tris[0].p1 = { -0.5,-0.5,-0.5, 1.0 };
	tris[0].p2 = { 0.5,-0.5,-0.5, 1.0 };
	tris[0].p3 = { 0.5,0.5,-0.5, 1.0 };

	tris[1].p1 = { -0.5,-0.5,-0.5, 1.0 };
	tris[1].p2 = { 0.5,0.5,-0.5, 1.0 };
	tris[1].p3 = { -0.5,0.5,-0.5, 1.0 };

	tris[2].p1 = { -0.5,-0.5,0.5, 1.0 };
	tris[2].p2 = { -0.5,-0.5,-0.5, 1.0 };
	tris[2].p3 = { -0.5,0.5,-0.5, 1.0 };

	tris[3].p1 = { -0.5,-0.5,0.5, 1.0 };
	tris[3].p2 = { -0.5,0.5,-0.5, 1.0 };
	tris[3].p3 = { -0.5,0.5,0.5, 1.0 };

	tris[4].p1 = { 0.5,-0.5,-0.5, 1.0 };
	tris[4].p2 = { 0.5,-0.5,0.5, 1.0 };
	tris[4].p3 = { 0.5,0.5,-0.5, 1.0 };

	tris[5].p1 = { 0.5,0.5,-0.5, 1.0 };
	tris[5].p2 = { 0.5,-0.5,0.5, 1.0 };
	tris[5].p3 = { 0.5,0.5,0.5, 1.0 };

	tris[6].p1 = { 0.5,-0.5,0.5, 1.0 };
	tris[6].p2 = { -0.5,-0.5,0.5, 1.0 };
	tris[6].p3 = { -0.5,0.5,0.5, 1.0 };

	tris[7].p1 = { 0.5,-0.5,0.5, 1.0 };
	tris[7].p2 = { -0.5,0.5,0.5, 1.0 };
	tris[7].p3 = { 0.5,0.5,0.5, 1.0 };


	

	FillConsole(buffer, WIDTH, HEIGHT);

	double angle = 0.0;



	while (true) {
		matrix_4x4 model = Create_Simple_Rotation(angle, { 0,0,1 });
		model = model * Create_Simple_Rotation(angle, { 1,0,0 });
		matrix_4x4 projection = Create_Projection((double)WIDTH / (double)HEIGHT, 90.0, 0.1, 100.0);
		matrix_4x4 veiw = Create_Veiw();

		for (int i = 0; i < 8; ++i) {
			tris1[i].p1 = projection * (veiw * (model * tris[i].p1));
			tris1[i].p2 = projection * (veiw * (model * tris[i].p2));
			tris1[i].p3 = projection * (veiw * (model * tris[i].p3));
		}

		for (int i = 0; i < 8; ++i) {
			DrawTriangle(tris1[i], buffer, WIDTH, HEIGHT);
		}

		WriteConsoleOutputA(hwnd, buffer, { (short)WIDTH,(short)HEIGHT }, { 0,0 }, &m_react);
		FillConsole(buffer, WIDTH, HEIGHT);

		angle += 1;
	}

}