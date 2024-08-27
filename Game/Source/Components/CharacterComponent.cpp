#include "CharacterComponent.h"
#include "Engine.h"
void CharacterComponent::Initialize()
{
	owner->transform = { {400, 300}, 0, 1 };
}

void CharacterComponent::Update(float dt)
{
	float rotate = 0;
	float thrust = 0;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_W))
	thrust = 1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = 1;



	owner->GetComponent<PhysicsComponent>()->ApplyTorque(rotate * 90 * dt);
	Vector2 direction = Vector2{ 1,0 }.Rotate(Math::DegToRad(owner->transform.rotation));
	owner->GetComponent<PhysicsComponent>()->ApplyForce(direction * speed * thrust);

	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE))
	{
		owner->GetComponent<PhysicsComponent>()->ApplyForce({0, -50});
	}
}

void CharacterComponent::OnCollisionEnter(Actor* actor)
{
	EVENT_NOTIFY(PlayerDead);
	EVENT_NOTIFY_DATA(AddPoints, 100);
}

void CharacterComponent::Read(const json_t& value)
{
	READ_DATA(value, speed);
}

void CharacterComponent::Write(json_t& value)
{
}
