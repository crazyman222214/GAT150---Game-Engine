#pragma once
#include "Components/Component.h"
class CharacterComponent : public Component
{
public:
	CLASS_DECLARATION(CharacterComponent)
	CLASS_PROTOTYPE(CharacterComponent)
	void Initialize() override;
	void Update(float dt) override;
	void OnCollisionEnter(Actor* actor);

	float speed = 0;
};