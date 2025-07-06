#include "stdafx.h"
#include "Bat.h"

Bat::Bat(const std::string& name) : GameObject(name)
{
}

void Bat::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	shape.setPosition(pos);
}

void Bat::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	shape.setRotation(rot);
}

void Bat::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	shape.setScale(s);
}

void Bat::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	shape.setOrigin(o);

}

void Bat::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(shape, preset);
	}
}

sf::Vector2f Bat::GetSize() const
{
	return shape.getSize();
}


void Bat::Init()
{
	shape.setSize({5.f, 100.f});
	shape.setFillColor(sf::Color::White);
	SetOrigin(Origins::MC);
}

void Bat::Release()
{
}

void Bat::Reset()
{
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
	//SetPosition({ (bounds.width - bounds.width) + 20.f, bounds.height * 0.5f }); SceneGame에서 설정 해줌

	sf::Vector2f size = shape.getSize();
	minX = bounds.left + size.x * 0.5f;
	maxX = (bounds.left + bounds.width) - size.x * 0.5f;
	minY = bounds.top + size.y * 0.5f;
	maxY = (bounds.top + bounds.height) - size.y * 0.5f;
}

void Bat::Update(float dt)
{
	if (isPaused) return;

	if (name == "Left Bat")
	{
		direction.y = InputMgr::GetAxis(Axis::VerticalLeft);
	}
	else if (name == "Right Bat")
	{
		direction.y = InputMgr::GetAxis(Axis::VerticalRight);
	}

	sf::Vector2f pos = GetPosition() + direction * speed * dt;
	pos.y = Utils::Clamp(pos.y, minY, maxY);
	SetPosition(pos);
}

void Bat::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}
