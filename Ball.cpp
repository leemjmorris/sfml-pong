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

void Ball::Init()
{
	shape.setRadius(10.f);
	shape.setFillColor(sf::Color::White);
	SetOrigin(Origins::ML);
}

void Ball::Release()
{
}

void Ball::Reset()
{
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
	SetPosition({ bounds.width * 0.5f, bounds.height - 20.f });

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

	if (pos.y < minY || pos.y > maxY)
	{
		direction.y *= -1.f;
	}

	if (pos.x < minX)
	{
		if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Game)
		{
			SceneGame* scene = (SceneGame*)SCENE_MGR.GetCurrentScene();
			scene->SetGameOver();
		}
	}

	if (pos.x > maxX)
	{
		if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Game)
		{
			SceneGame* scene = (SceneGame*)SCENE_MGR.GetCurrentScene();
			scene->SetGameOver();
		}
	}

	if (bat != nullptr)
	{
		const sf::FloatRect& batBounds = bat->GetGlobalBounds();
		if (shape.getGlobalBounds().intersects(batBounds))
		{
			pos.y = batBounds.top;
			direction.y *= -1.f;
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
