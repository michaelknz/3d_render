#include "render.h"

void DrawTriangle(triangled tr, CHAR_INFO* buf, int size_x, int size_y, double fov) {
	vector2d p1;
	vector2d p2;
	vector2d p3;

	p1.x = ((double)size_y / (double)size_x) * tr.p1.x / tan(M_PI * fov / 360.0) / tr.p1.z;
	p1.y = tr.p1.y / tan(M_PI * fov / 360.0) / tr.p1.z;

	p2.x = ((double)size_y / (double)size_x) * tr.p2.x / tan(M_PI * fov / 360.0) / tr.p2.z;
	p2.y = tr.p2.y / tan(M_PI * fov / 360.0) / tr.p2.z;

	p3.x = ((double)size_y / (double)size_x) * tr.p3.x / tan(M_PI * fov / 360.0) / tr.p3.z;
	p3.y = tr.p3.y / tan(M_PI * fov / 360.0) / tr.p3.z;

	p1.x *= ((double)size_x - 1);
	p1.y *= ((double)size_y - 1);

	p2.x *= ((double)size_x - 1);
	p2.y *= ((double)size_y - 1);

	p3.x *= ((double)size_x - 1);
	p3.y *= ((double)size_y - 1);


	if (p1.x < (double)size_x && p1.x >= 0 && p1.y < (double)size_y && p1.y >= 0) {
		buf[(int)p1.y * size_x + (int)p1.x].Char.UnicodeChar = L' ';
		buf[(int)p1.y * size_x + (int)p1.x].Attributes = 15 << 4;
	}

	if (p2.x < (double)size_x && p2.x >= 0 && p2.y < (double)size_y && p2.y >= 0) {
		buf[(int)p2.y * size_x + (int)p2.x].Char.UnicodeChar = L' ';
		buf[(int)p2.y * size_x + (int)p2.x].Attributes = 15 << 4;
	}

	if (p3.x < (double)size_x && p3.x >= 0 && p3.y < (double)size_y && p3.y >= 0) {
		buf[(int)p3.y * size_x + (int)p3.x].Char.UnicodeChar = L' ';
		buf[(int)p3.y * size_x + (int)p3.x].Attributes = 15 << 4;
	}

	DrawLine(buf, size_x, size_y, p1, p2);
	DrawLine(buf, size_x, size_y, p2, p3);
	DrawLine(buf, size_x, size_y, p3, p1);
}

void FillConsole(CHAR_INFO* buf, int size_x, int size_y) {
	for (int i = 0; i < size_y; ++i) {
		for (int j = 0; j < size_x; ++j) {
			buf[i * size_x + j].Char.UnicodeChar = L' ';
			buf[i * size_x + j].Attributes = 0;
		}
	}
}

void DrawLine(CHAR_INFO* buf, int size_x, int size_y, vector2d p1, vector2d p2) {
	vector2i del;
	del.x = p2.x - p1.x;
	del.y = p2.y - p1.y;

	if (del.x != 0) {
		double dx = (double)del.y / (double)abs(del.x);

		for (int i = 1; i <= abs(del.x); ++i) {
			int x = p1.x + i*(del.x/abs(del.x));
			int y = (double)p1.y + ((double)i * dx);
			if (x >= 0 && x < size_x && y >= 0 && y < size_y) {
				buf[y * size_x + x].Char.UnicodeChar = L' ';
				buf[y * size_x + x].Attributes = 15 << 4;
			}
		}
	}

	if (del.y != 0) {
		double dy = (double)del.x / (double)abs(del.y);

		for (int i = 1; i <= abs(del.y); ++i) {
			int x = (double)p1.x + ((double)i * dy);
			int y = p1.y + i*(del.y/abs(del.y));
			if (x >= 0 && x < size_x && y >= 0 && y < size_y) {
				buf[y * size_x + x].Char.UnicodeChar = L' ';
				buf[y * size_x + x].Attributes = 15 << 4;
			}
		}
	}
}

matrix_3x3 Create_Simple_Rotation(double angle, vector3i axis) {
	matrix_3x3 output;
	if (axis.x == 1) {
		output.mas[0] = 1;
		output.mas[3] = 0;
		output.mas[6] = 0;

		output.mas[1] = 0;
		output.mas[4] = cos(M_PI * angle / 180.0);
		output.mas[7] = sin(M_PI * angle / 180.0);

		output.mas[2] = 0;
		output.mas[5] = -sin(M_PI * angle / 180.0);
		output.mas[8] = cos(M_PI * angle / 180.0);
	}

	else if (axis.y == 1) {
		output.mas[0] = cos(M_PI * angle / 180.0);
		output.mas[3] = 0;
		output.mas[6] = sin(M_PI * angle / 180.0);

		output.mas[1] = 0;
		output.mas[4] = 1;
		output.mas[7] = 0;

		output.mas[2] = -sin(M_PI * angle / 180.0);
		output.mas[5] = 0;
		output.mas[8] = cos(M_PI * angle / 180.0);
	}

	else if (axis.z == 1) {
		output.mas[0] = cos(M_PI * angle / 180.0);
		output.mas[3] = -sin(M_PI * angle / 180.0);
		output.mas[6] = 0;

		output.mas[1] = sin(M_PI * angle / 180.0);
		output.mas[4] = cos(M_PI * angle / 180.0);
		output.mas[7] = 0;

		output.mas[2] = 0;
		output.mas[5] = 0;
		output.mas[8] = 1;
	}
	return output;
}

void Move_Mesh(triangled* tris, int size, vector3d movement) {
	for (int i = 0; i < size; ++i) {
		tris[i].p1.x += movement.x;
		tris[i].p1.y += movement.y;
		tris[i].p1.z += movement.z;

		tris[i].p2.x += movement.x;
		tris[i].p2.y += movement.y;
		tris[i].p2.z += movement.z;

		tris[i].p3.x += movement.x;
		tris[i].p3.y += movement.y;
		tris[i].p3.z += movement.z;
	}
}

vector3d operator *(matrix_3x3 mat, vector3d vec) {
	vector3d output;
	output.x = mat.mas[0] * vec.x + mat.mas[1] * vec.y + mat.mas[2] * vec.z;
	output.y = mat.mas[3] * vec.x + mat.mas[4] * vec.y + mat.mas[5] * vec.z;
	output.z = mat.mas[6] * vec.x + mat.mas[7] * vec.y + mat.mas[8] * vec.z;
	return output;
}