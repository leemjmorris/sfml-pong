#pragma once
#include "Scene.h"
#include "UiMgr.h"

class Bat;
class Ball;

class SceneGame : public Scene
{
protected:
	sf::Font ScoreFont;

	UiMgr* uiMgr = nullptr;	
	Bat* batLeft = nullptr;
	Bat* batRight = nullptr;

	Ball* ball = nullptr;

	bool isGameOver = false;

	int scoreLeft = 0;
	int scoreRight = 0;

public:
	SceneGame();
	~SceneGame() override = default;

	bool ballActive = false;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetGameOver();
	void AddScoreLeft();
	void AddScoreRight();

	bool IsGameOver() const { return isGameOver; }

};

