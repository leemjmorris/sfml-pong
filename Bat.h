#pragma once
#include "GameObject.h"

class Bat : public GameObject
{
protected:
	sf::RectangleShape shape;

	float speed = 500.f;
	sf::Vector2f direction;

	float minX = 0.f;
	float maxX = 0.f;
	float minY = 0.f;
	float maxY = 0.f;

	bool isPaused = false;

public:
	Bat(const std::string& name = "");
	~Bat() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	sf::Vector2f GetSize() const;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetPaused(bool paused) { isPaused = paused; }

	sf::FloatRect GetGlobalBounds() { return shape.getGlobalBounds(); }
};

