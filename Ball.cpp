#include "stdafx.h"
#include "Ball.h"
#include "Bat.h"
#include "SceneGame.h"

Ball::Ball(const std::string& name)
	: GameObject(name)
{
}

void Ball::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	shape.setPosition(pos);
}

void Ball::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	shape.setRotation(rot);
}

void Ball::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	shape.setScale(s);
}

void Ball::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	shape.setOrigin(o);
}

void Ball::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(shape, preset);
	}
}

float Ball::GetRadius() const
{
	return shape.getRadius();
}

void Ball::SetBat(Bat* left, Bat* right)
{
	batLeft = left;
	batRight = right;
}

void Ball::Init()
{
	shape.setRadius(10.f);
	shape.setFillColor(sf::Color::White);
	SetOrigin(Origins::MC);
}

void Ball::Release()
{
}

void Ball::Reset()
{	
	//SceneGame* scene = (SceneGame*)SCENE_MGR.GetCurrentScene();
	//scene->ballActive = true;

	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
	sf::Vector2f batPos = batLeft->GetPosition();
	float ballOffsetX = batLeft->GetSize().x * 0.5f + this->GetRadius();

	sf::Vector2f ballStartPos = batPos + sf::Vector2f(ballOffsetX, 0.f);
	this->SetPosition(ballStartPos);

	float offset = batLeft->GetSize().x * 0.5f + shape.getRadius();
	SetPosition(batPos + sf::Vector2f(offset, 0.f));

	float radius = shape.getRadius();
	minX = bounds.left + radius * 2.f;
	maxX = (bounds.left + bounds.width) - radius * 2.f;

	minY = bounds.top + radius;
	maxY = bounds.top + bounds.height;

	direction = { 0.f, 0.f };
	speed = 0.f;	
}

void Ball::Update(float dt)
{
	sf::Vector2f pos = GetPosition() + direction * speed * dt;

	float margin = shape.getRadius();
	if (pos.y < minY + margin || pos.y > maxY - margin)
	{
		direction.y *= -1.f;
	}

	if (pos.x < minX)
	{
		if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Game)
		{
			SceneGame* scene = (SceneGame*)SCENE_MGR.GetCurrentScene();

			if (!scene->IsGameOver())
			{
				scene->AddScoreRight();
				scene->ballActive = false;
				direction = { 0.f, 0.f };
				speed = 0.f;
				Reset();
				//scene->SetGameOver();
			}

		}
	}

	if (pos.x > maxX)
	{
		if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Game)
		{
			SceneGame* scene = (SceneGame*)SCENE_MGR.GetCurrentScene();

			if (!scene->IsGameOver())
			{
				scene->AddScoreLeft();
				scene->ballActive = false;
				direction = { 0.f, 0.f };
				speed = 0.f;
				Reset();
				//scene->SetGameOver();
			}
		}
	}

	if (batLeft != nullptr)
	{
		const sf::FloatRect& batBounds = batLeft->GetGlobalBounds();

		if (shape.getGlobalBounds().intersects(batBounds))
		{
			direction.x *= -1.f;
			pos.x = batBounds.left + batBounds.width + shape.getRadius();
		}		
	}

	if (batRight != nullptr)
	{
		const sf::FloatRect& bounds = batRight->GetGlobalBounds();
		if (shape.getGlobalBounds().intersects(bounds))
		{
			direction.x *= -1.f;
			pos.x = bounds.left - shape.getRadius();
		}
	}

	SetPosition(pos);
}

void Ball::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

void Ball::Fire(const sf::Vector2f& d, float s)
{
	direction = d;
	speed = s;
}


