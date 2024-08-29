#include "PlayerComponent.h"
#include "Engine.h"
#include "CharacterComponent.h"
void PlayerComponent::Initialize()
{
	if (owner->name == "Player")owner->transform = { {200, 200}, 0, 1 };
	else if (owner->name == "OtherPlayer") owner->transform = { {400, 200}, 0, 1 };
	groundCount = 0;
	
	owner->OnCollisionEnter = std::bind(&PlayerComponent::OnCollisionEnter, this, std::placeholders::_1);

	owner->OnCollisionExit = std::bind(&PlayerComponent::OnCollisionExit, this, std::placeholders::_1);

}

void PlayerComponent::Update(float dt)
{
	bool onGround = (groundCount > 0);

	Vector2 direction{0,0};

	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_W)) 
	{
		//owner->scene->engine->GetNetwork().sendMessageToHost("You dumb and smell");

	}
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_A) && owner->name == "Player") direction.x = -1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_D) && owner->name == "Player") direction.x = 1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_LEFT) && owner->name == "OtherPlayer") direction.x = -1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_RIGHT) && owner->name == "OtherPlayer") direction.x = 1;



	if (onGround && owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_W) && owner->name == "Player")
	{
		owner->GetComponent<PhysicsComponent>()->SetVelocity(Vector2{owner->GetComponent<PhysicsComponent>()->velocity.x, -200.0f});
		owner->GetComponent<AudioComponent>()->Play();
	}

	if (onGround && owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_UP) && owner->name == "OtherPlayer")
	{
		owner->GetComponent<PhysicsComponent>()->SetVelocity(Vector2{ owner->GetComponent<PhysicsComponent>()->velocity.x, -200.0f });
		owner->GetComponent<AudioComponent>()->Play();
	}
	
	owner->GetComponent<PhysicsComponent>()->ApplyForce(direction * speed);
}

void PlayerComponent::OnCollisionEnter(Actor* actor)
{

	if (actor->tag == "Ground") groundCount++;
	if (actor->tag == "Player")
	{

		int actorBottomPosition = actor->transform.position.y - actor->GetComponent<Box2DPhysicsComponent>()->size.y;
		int ownerTopPosition = owner->transform.position.y + owner->GetComponent<Box2DPhysicsComponent>()->size.y;

		if ((actorBottomPosition + 12) > ownerTopPosition)
		{

			if (actor->name == "Player")
			{
				EVENT_NOTIFY(PlayerDead);

			}
			if (actor->name == "OtherPlayer") EVENT_NOTIFY(OtherPlayerDead);
		}
	}
}

void PlayerComponent::OnCollisionExit(Actor* actor)
{
	if (actor->tag == "Ground")
	{
		groundCount--;
	}
}

void PlayerComponent::Read(const json_t& value)
{
	READ_DATA(value, speed);
}

void PlayerComponent::Write(json_t& value)
{
}
