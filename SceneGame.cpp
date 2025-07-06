#include "stdafx.h"
#include "SceneGame.h"
#include "Bat.h"
#include "Ball.h"

SceneGame::SceneGame() : Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	float winWidth = FRAMEWORK.GetWindowBounds().width;
	float winHeight = FRAMEWORK.GetWindowBounds().height;


	batLeft = (Bat*)AddGameObject(new Bat("Left Bat"));
	batLeft->Init();
	batLeft->SetPosition({ 30.f, winHeight * 0.5f });

	batRight = (Bat*)AddGameObject(new Bat("Right Bat"));
	batRight->Init();
	batRight->SetPosition({ winWidth - 30.f, winHeight * 0.5f });
	
	ball = (Ball*)AddGameObject(new Ball("Ball"));
	

	ball->SetBat(batLeft);

	Scene::Init();
}

void SceneGame::Enter()
{
	ballActive = false;
	ball->Reset();

	Scene::Enter();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	if (!ballActive)
	{
		ball->SetPosition(batLeft->GetPosition());

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
	SCENE_MGR.ChangeScene(SceneIds::Game);
}
