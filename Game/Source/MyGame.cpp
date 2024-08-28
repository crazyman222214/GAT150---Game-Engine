#include "MyGame.h"
#include "Engine.h"
#include "Event/EventSystem.h"
#include "Components/RocketComponent.h"

#include <memory>
bool MyGame::Initialize()
{
	m_scene = std::make_unique<Scene>(m_engine, new rapidjson::Document);

	Json::Load("Scene/scene.json", *(m_scene->document));
	m_scene->Read(*(m_scene->document));
	rapidjson::Document document;
	Json::Load("Scene/tilemap.json", document);
	m_scene->Read(document);
	m_scene->Initialize();

	ADD_OBSERVER(PlayerDead, MyGame::OnPlayerDead)
	ADD_OBSERVER(OtherPlayerDead, MyGame::OnOtherPlayerDead)
	ADD_OBSERVER(ADDPoints, MyGame::OnAddPoints)

	
    return true;
}

void MyGame::Shutdown()
{
	//Json::Save("Scene/scene.json", *(m_scene->document));
	m_scene->RemoveAll();
}

void MyGame::Update(float dt)
{
	switch (gameState)
	{
	case GameState::TITLE:
		if (m_scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE))
		{
			gameState = GameState::START_GAME;
		}
		break;
	case GameState::START_GAME:
	{
		gameState = GameState::GAME;
	}
		break;
	case GameState::GAME:
		m_scene->Update(m_engine->GetTime().GetDeltaTime());
		break;
	case GameState::GAME_OVER:
		m_scene->GetActor<Actor>("Player")->GetComponent<Box2DPhysicsComponent>()->DestroyRigidBody();
		m_scene->GetActor<Actor>("OtherPlayer")->GetComponent<Box2DPhysicsComponent>()->DestroyRigidBody();
		m_scene->RemoveAll();
		m_scene = std::make_unique<Scene>(m_engine, new rapidjson::Document);

		Json::Load("Scene/scene.json", *(m_scene->document));
		m_scene->Read(*(m_scene->document));
		rapidjson::Document document;
		Json::Load("Scene/tilemap.json", document);
		m_scene->Read(document);

		m_scene->Initialize();

		gameState = GameState::START_GAME;
		break;
	};


}

void MyGame::Draw(Renderer& renderer)
{
	m_scene->Draw(renderer);
}

void MyGame::OnPlayerDead(const Event& event)
{
	std::cout << "Game Player dead. L\n";
	gameState = GameState::GAME_OVER;
	
}

void MyGame::OnOtherPlayerDead(const Event& event)
{
	std::cout << "Game Player dead. L\n";
	gameState = GameState::GAME_OVER;

}
void MyGame::OnAddPoints(const Event& event)
{
	m_score += std::get<int>(event.data);
	//std::cout << m_score << std::endl;
}
