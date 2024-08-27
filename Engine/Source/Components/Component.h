#pragma once
#include "Framework/Object.h"
#include "Core/Factory.h"


class Component : public Object
{
public:
	virtual void Update(float dt) = 0;
	class Actor* owner{nullptr};
};