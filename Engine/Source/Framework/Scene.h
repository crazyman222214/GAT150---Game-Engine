#pragma once
#include "../Math/Vector2.h"
#include <list>
#include <memory>

class Renderer;
class Game;
class Actor;

class Scene
{
public:
	//Scene() = default;
	Scene(Game* game) : m_game{ game } {}
	
	void Update(float dt);
	void Draw(Renderer& renderer);

	void AddActor(std::unique_ptr<Actor> actor);
	void RemoveAll();
	void CheckForCollisions();

	template<typename T>
	T* GetActor();

	Game* GetGame() { return m_game; }

	Actor* GetActorFromPosition(Vector2 position);
	Actor* GetClosestEnemyWithinRadius(Actor& actor, float radius);

	bool AreThereEnemies();
	

protected:
	std::list<std::unique_ptr<Actor>> m_actors;

	Game* m_game{ nullptr };
};

template<typename T>
T* Scene::GetActor()
{
	for (auto& actor : m_actors)
	{
		T* result = dynamic_cast<T*>(actor.get());
		if (result) return result;
	}
	return nullptr;
}