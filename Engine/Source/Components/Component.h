#pragma once
#include "Framework/Object.h"


class Component : public Object
{
public:
	virtual void Update(float dt) = 0;
	class Actor* owner{nullptr};
};