#pragma once
class Engine;
class Renderer;
class Scene;
class Game
{
public:
	Game() = default;
	Game(Engine* engine) : m_engine{ engine } {}

	virtual bool Initialize() = 0;
	virtual void Shutdown() = 0;

	virtual void Update(float dt) = 0;
	virtual void Draw(Renderer& renderer) = 0;

	int GetScore() const { return m_currentRound; }
	void NextRound() { m_currentRound++; }

	int GetLives() const { return m_lives; }
	void LoseLife() { m_lives--; }


	bool isHost = false;

protected:
	Engine* m_engine{ nullptr };
	int m_currentRound = 0;
	int m_maxRounds = 0;
	int m_lives = 0;
	int m_playerScore = 0;
	int m_otherPlayerScore = 0;
};