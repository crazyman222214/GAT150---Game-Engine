#include "Scene.h"
#include "../Renderer/Actor.h"
#include "Core/Factory.h"
#include <algorithm>
#include <memory>
#include <iostream>


void Scene::Initialize()
{
	for (auto& actor : actors)
	{
		actor->Initialize();
	}
}

/// <summary>
/// Updates all actors and checks for collisions
/// </summary>
/// <param name="dt">The delta time between the last frame and the current frame</param>
void Scene::Update(float dt)
{
	for (auto& actor : actors)
	{
		if (actor->active) actor->Update(dt);
	}

	std::erase_if(actors, [](auto& actor) {return actor->destroyed; });
	//CheckForCollisions();
}

/// <summary>
/// Checks for collisions and handles calling the colliding actor's OnCollision
/// </summary>
void Scene::CheckForCollisions()
{
	

	/*for (auto& actor1 : m_actors)
	{
		for (auto& actor2 : m_actors)
		{
			if (actor1 == actor2 || (actor1->destroyed || actor2->destroyed)) continue;

			Vector2 direction = actor1->GetTransform().position - actor2->GetTransform().position;
			float distance = direction.Length();

			float radius = actor1->GetRadius() + actor2->GetRadius();

			if (distance <= radius)
			{
				actor1->OnCollision(actor2.get());
				actor2->OnCollision(actor1.get());
			}

		}
	}*/
}

void Scene::Read(const json_t& value)
{
	if (HAS_DATA(value, actors) && GET_DATA(value, actors).IsArray())
	{
		for (auto& actorValue : GET_DATA(value, actors).GetArray())
		{
			auto actor = Factory::Instance().Create<Actor>(Actor::GetTypeName());
			actor->Read(actorValue);

			AddActor(std::move(actor));
		}
	}
}

void Scene::Write(json_t& value)
{
}

/// <summary>
/// Draws all actors in the scene
/// </summary>
/// <param name="renderer">The Renderer that renders the actors</param>
void Scene::Draw(Renderer& renderer)
{
	for (auto& actor : actors)
	{
		
		if (actor->active) actor->Draw(renderer);
	}
}

/// <summary>
/// Adds an actor into the scene
/// </summary>
/// <param name="actor">A unique pointer to the actor you want to add to the scene</param>
void Scene::AddActor(std::unique_ptr<Actor> actor)
{
	
	actor->scene = this;
	actors.push_back(std::move(actor));
}

/// <summary>
/// Removes all actors from the scene
/// </summary>
void Scene::RemoveAll()
{
	actors.clear();
}

/// <summary>
/// Gets an actor from a given position, Ignoring Visual Actors
/// </summary>
/// <param name="position">The given position we are checking for actors with</param>
/// <returns>returns the actor in the given position</returns>
Actor* Scene::GetActorFromPosition(Vector2 position)
{
	for (auto& actor : actors)
	{
		//I will never want to get the visual actors from this method
		//if (actor.get()->GetTag() == "Visual") continue;

		//Vector2 direction = position - actor.get()->transform.position;
		//float distance = direction.Length();
		////float radius = actor.get()->GetRadius();

		//if (distance <= radius)
		//{

		//	return actor.get();
		//}
	}
	return nullptr;
}


Actor* Scene::GetClosestEnemyWithinRadius(Actor& actor, float radius)
{
	Actor* closestEnemy{nullptr};
	float closestDistance = 0.0f;
	for (auto& enemy : actors)
	{
		//if (enemy.get()->GetTag() == "Enemy")
		{
			Vector2 direction =  actor.transform.position - enemy.get()->transform.position;
			float distance = direction.Length();

			if (distance <= radius)
			{
				if (!closestEnemy)
				{
					closestEnemy = enemy.get();
					closestDistance = distance;
				}
				else if (closestDistance <= distance)
				{
					closestEnemy = enemy.get();
					closestDistance = distance;
				}
			}
			
		}
	}
	return closestEnemy;
}

bool Scene::AreThereEnemies()
{
	for (auto& actor : actors)
	{
		//if (actor.get()->GetTag() == "Enemy") return true;
	}
	return false;
}



