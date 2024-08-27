#include "Scene.h"
#include "../Renderer/Actor.h"
#include "Core/Factory.h"
#include "Core/EAssert.h"
#include "Engine.h"
#include "Core/Net.h"
#include "Game.h"
#include <algorithm>
#include <memory>
#include <iostream>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>


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
		if (actor->active)
		{
			actor->Update(dt);
		}
	}

	std::erase_if(actors, [](auto& actor) {return actor->destroyed; });
	Write(*document);


	//engine->GetNetwork().sendMessage();

	//Each update I need to get the json value for the player actor and send that as a packet to the connected peer
	//Once you get the packet. it should take the packet and change any changes that need to be made for its local
	//data for the other player

}

Scene::Scene(const Scene& other)
{
	ASSERT(false);
}

void Scene::Read(const json_t& value)
{
	if (HAS_DATA(value, actors) && GET_DATA(value, actors).IsArray())
	{
		for (auto& actorValue : GET_DATA(value, actors).GetArray())
		{
			auto actor = Factory::Instance().Create<Actor>(Actor::GetTypeName());
			actor->Read(actorValue);

			bool prototype = false;
			READ_DATA(actorValue, prototype);
			if (prototype)
			{
				std::string name = actor->name;
				Factory::Instance().RegisterPrototype<Actor>(name, std::move(actor));
			}
			else
			{
				AddActor(std::move(actor));
			}

		}
	}
}

void Scene::Write(json_t& value)
{
	if (HAS_DATA(value, actors) && GET_DATA(value, actors).IsArray())
	{
		auto actorsJSON = GET_DATA(value, actors).GetArray();
		auto actor = actors.begin();
		for (int i = 0; i < actorsJSON.Size(); i++)
		{
			actor->get()->Write(actorsJSON[i]);

			if (actor->get()->name == "Player")
			{
				//As it writes the json, it should serialize the data and send the packet

				//String version of the actor

				rapidjson::StringBuffer strbuf;
				strbuf.Clear();

				rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
				document->Accept(writer);

				std::string stringPlayer = strbuf.GetString();
				//std::cout << stringPlayer;

				//engine->GetNetwork().sendMessageToClient("You a bitch");
				//Needs to know which type of client it is talking to.

				//(game->isHost) ? engine->GetNetwork().sendMessageToClient(stringPlayer + ":Host") : engine->GetNetwork().sendMessageToHost(stringPlayer + ":Client");

			}

			//increments the iterator: actor
			if (!(actor == actors.end())) std::advance(actor, 1);
		}
		
	}
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
void Scene::AddActor(std::unique_ptr<Actor> actor, bool initialize)
{
	actor->scene = this;
	if (initialize) actor->Initialize();

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



