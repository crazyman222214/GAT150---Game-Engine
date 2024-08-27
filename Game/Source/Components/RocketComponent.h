#pragma once
#include "Components/Component.h"

class RocketComponent : public Component
{
public:
	CLASS_DECLARATION(RocketComponent)
	CLASS_PROTOTYPE(RocketComponent)



		// Inherited via Component
		void Initialize() override;

	void Update(float dt) override;

};