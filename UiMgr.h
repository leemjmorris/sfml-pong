#pragma once
#include "GameObject.h"
class UiMgr : public GameObject
{
private:
    sf::Text scoreTextLeft;
    sf::Text scoreTextRight;
    sf::Text restartText;

    sf::Font* font = nullptr;

    bool showRestartText = false;

public:
    UiMgr(const std::string& name);

    void Init() override;
    void Release() override;
    void Reset() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;

    void SetScores(int leftScore, int rightScore);

    void SetFont(const sf::Font& font);

    void ShowRestartMessage(bool show);

};

