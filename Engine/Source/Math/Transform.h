#pragma once
#include "Vector2.h"
#include "Core/Serializable.h"

struct Transform : public Serializable
{
	Vector2 position;
	float rotation = 0;
	float scale = 1; //Make this into a vector2 so that x and y can be scaled independently


	Transform() = default;
	Transform(Vector2 position, float rotation = 0, float scale = 1) : position{ position }, rotation{ rotation }, scale{ scale } {}

	void Read(const json_t& value) override;
	void Write(json_t& value) override;
};