#pragma once
#include "GameObject.h"
class UiMgr : public GameObject
{
private:
    sf::Text scoreTextLeft;
    sf::Text scoreTextRight;

    sf::Font* font = nullptr;

public:
    UiMgr(const std::string& name);

    void Init() override;
    void Release() override;
    void Reset() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;

    void SetScores(int leftScore, int rightScore);

    void SetFont(const sf::Font& font);


};

