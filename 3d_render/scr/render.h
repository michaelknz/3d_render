#pragma once
#define _USE_MATH_DEFINES
#include <Windows.h>
#include <stdio.h>
#include <math.h>

struct vector3i {
	int x;
	int y;
	int z;
};

struct trianglei {
	vector3i p1;
	vector3i p2;
	vector3i p3;
};

struct vector3d {
	double x;
	double y;
	double z;
};

struct triangled {
	vector3d p1;
	vector3d p2;
	vector3d p3;
};

struct vector2d {
	double x;
	double y;
};

struct vector2i {
	int x;
	int y;
};

void DrawTriangle(triangled tr, CHAR_INFO* buf, int size_x, int size_y, double fov);
void FillConsole(CHAR_INFO* buf, int size_x, int size_y);
void DrawLine(CHAR_INFO* buf, int size_x, int size_y, vector2d p1, vector2d p2);