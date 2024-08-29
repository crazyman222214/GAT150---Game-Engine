#pragma once
#include "Framework/Game.h"
#include "Event/EventSystem.h"
#include <memory>
class MyGame : public Game, Observer
{
public:

	enum class GameState
	{
		TITLE,
		START_GAME,
		GAME,
		GAME_OVER
		
	};

	MyGame() = default;
	MyGame(Engine* engine) : Game{ engine } {}

	bool Initialize() override;
	void Shutdown() override;
	void Update(float dt) override;
	void Draw(Renderer& renderer) override;

	void OnPlayerDead(const Event& event);
	void OnOtherPlayerDead(const Event& event);

private:
	std::unique_ptr<class Scene> m_scene;
	GameState gameState = GameState::TITLE;
};