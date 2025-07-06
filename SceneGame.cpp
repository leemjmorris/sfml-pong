#include "stdafx.h"
#include "SceneGame.h"
#include "Bat.h"
#include "Ball.h"
#include "UiMgr.h"

SceneGame::SceneGame() : Scene(SceneIds::Game)
{
}

void SceneGame::AddScoreLeft()
{
	scoreLeft += 10;
}

void SceneGame::AddScoreRight()
{
	scoreRight += 10;
}


void SceneGame::Init()
{
	ScoreFont.loadFromFile("fonts/DS-DIGIT.TTF");

	uiMgr = (UiMgr*)AddGameObject(new UiMgr("UI"));
	uiMgr->SetFont(ScoreFont);

	
	float winWidth = FRAMEWORK.GetWindowBounds().width;
	float winHeight = FRAMEWORK.GetWindowBounds().height;


	batLeft = (Bat*)AddGameObject(new Bat("Left Bat"));
	batLeft->Init();
	batLeft->SetPosition({ 30.f, winHeight * 0.5f });

	batRight = (Bat*)AddGameObject(new Bat("Right Bat"));
	batRight->Init();
	batRight->SetPosition({ winWidth - 30.f, winHeight * 0.5f });
	
	ball = (Ball*)AddGameObject(new Ball("Ball"));
	
	ball->SetBat(batLeft, batRight);

	Scene::Init();
}

void SceneGame::Enter()
{
	scoreLeft = 0;
	scoreRight = 0;
	
	isGameOver = false;
	ballActive = false;
	ball->Reset();

	batLeft->SetPaused(false);
	batRight->SetPaused(false);

	uiMgr->ShowRestartMessage(false);

	Scene::Enter();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);

	if (!isGameOver && (scoreLeft >= 100 || scoreRight >= 100))
	{
		SetGameOver();
		
	

		ball->Reset();		
		batLeft->Reset();
		batRight->Reset();
		return;
	}

	if (isGameOver)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::E))
		{
			SCENE_MGR.ChangeScene(SceneIds::Game);
		}
		return;
	}


	if (!ballActive)
	{
		sf::Vector2f batPos = batLeft->GetPosition();
		float ballOffsetX = batLeft->GetSize().x * 0.5f + ball->GetRadius();

		sf::Vector2f ballStartPos = batPos + sf::Vector2f(ballOffsetX, 0.f);
		ball->SetPosition(ballStartPos);

		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			ballActive = true;

			sf::Vector2f dir(1.f, -1.f);
			Utils::Nomalize(dir);
			ball->Fire(dir, 500.f);
		}
	}
}

void SceneGame::SetGameOver()
{
	isGameOver = true;

	batLeft->SetPaused(true);
	batRight->SetPaused(true);
	ballActive = false;

	uiMgr->ShowRestartMessage(true);

	//SCENE_MGR.ChangeScene(SceneIds::Game);
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	uiMgr->SetScores(scoreLeft, scoreRight);
	uiMgr->Draw(window);
}
