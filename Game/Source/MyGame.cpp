#include "MyGame.h"
#include "Engine.h"
#include "Event/EventSystem.h"

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
	ADD_OBSERVER(ADDPoints, MyGame::OnAddPoints)

	
    return true;
}

void MyGame::Shutdown()
{
	Json::Save("Scene/scene.json", *(m_scene->document));
	m_scene->RemoveAll();
}

void MyGame::Update(float dt)
{
	m_scene->Update(m_engine->GetTime().GetDeltaTime());
}

void MyGame::Draw(Renderer& renderer)
{
	m_scene->Draw(renderer);
}

void MyGame::OnPlayerDead(const Event& event)
{
	std::cout << "Game Player dead. L\n";
}

void MyGame::OnAddPoints(const Event& event)
{
	m_score += std::get<int>(event.data);
	//std::cout << m_score << std::endl;
}
