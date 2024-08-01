#pragma once
#include "Vector2.h"

struct Transform
{
	Vector2 position;
	float rotation;
	float scale; //Make this into a vector2 so that x and y can be scaled independently


	Transform() = default;
	Transform(Vector2 position, float rotation = 0, float scale = 1) : position{ position }, rotation{ rotation }, scale{ scale } {}
};