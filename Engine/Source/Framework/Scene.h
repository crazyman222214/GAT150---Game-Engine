#pragma once
#include "../Math/Vector2.h"
#include "Object.h"
#include <list>
#include <memory>

class Renderer;
class Game;
class Actor;
class Engine;

class Scene : public Object
{
public:
	
	Scene(Engine* engine, Game* game = nullptr) : engine{engine}, game { game } {}
	
	CLASS_DECLARATION(Scene)

	void Update(float dt);
	void Draw(Renderer& renderer);

	void AddActor(std::unique_ptr<Actor> actor);
	void RemoveAll();
	void CheckForCollisions();

	template<typename T> T* GetActor();
	template<typename T> T* GetActor(const std::string& name);


	Game* game{ nullptr };
	Engine* engine{ nullptr };


	Actor* GetActorFromPosition(Vector2 position);
	Actor* GetClosestEnemyWithinRadius(Actor& actor, float radius);

	bool AreThereEnemies();
	// Inherited via Object
	void Initialize() override;
	

protected:
	std::list<std::unique_ptr<Actor>> actors;



};

template<typename T>
T* Scene::GetActor()
{
	for (auto& actor : actors)
	{
		T* result = dynamic_cast<T*>(actor.get());
		if (result) return result;
	}
	return nullptr;
}

template<typename T>
inline T* Scene::GetActor(const std::string& name)
{
	for (auto& actor : actors)
	{
		T* result = dynamic_cast<T*>(actor.get());

		if (result && IsEqualIgnoreCase( result->name, name)) return result;
	}
	return nullptr;
}
