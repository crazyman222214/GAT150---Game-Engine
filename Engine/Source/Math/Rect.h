#pragma once

struct Rect
{
	int x = 0;
	int y = 0;
	int width = 0;
	int height = 0;

	Rect() = default;
	Rect(int x, int y, int width, int height) : x{ x }, y{ y }, height{ height }, width{ width } {}
};