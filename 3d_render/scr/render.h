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

struct triangle3i {
	vector3i p1;
	vector3i p2;
	vector3i p3;
};

struct vector3d {
	double x;
	double y;
	double z;
};

struct triangle3d {
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

struct matrix_3x3 {
	double mas[9];
};

struct vector4d {
	double x;
	double y;
	double z;
	double w;
};

struct vector4i {
	int x;
	int y;
	int z;
	int w;
};

struct matrix_4x4 {
	double mas[16];
};

struct triangle4d {
	vector4d p1;
	vector4d p2;
	vector4d p3;
};

struct triangle4i {
	vector4i p1;
	vector4i p2;
	vector4i p3;
};

void DrawTriangle(triangle4d tr, CHAR_INFO* buf, int size_x, int size_y);
void FillConsole(CHAR_INFO* buf, int size_x, int size_y);
void DrawLine(CHAR_INFO* buf, int size_x, int size_y, vector2d p1, vector2d p2);
matrix_4x4 Create_Simple_Rotation(double angle, vector3i axis);
matrix_4x4 Create_Projection(double asp, double fov, double znear, double zfar);
matrix_4x4 Create_Identity();
matrix_4x4 Create_Veiw();
void Move_Mesh(triangle3d* tris, int size, vector3d movement);

vector4d operator *(matrix_4x4 mat, vector4d vec);
matrix_4x4 operator *(matrix_4x4 mat1, matrix_4x4 mat2);
