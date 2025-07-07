#include "stdafx.h"
#include "UiMgr.h"
#include "ResourceMgr.h"
#include "Framework.h"

UiMgr::UiMgr(const std::string& name)
{
}

void UiMgr::SetScores(int leftScore, int rightScore)
{
    scoreTextLeft.setString("Player 1: " + std::to_string(leftScore));
    scoreTextRight.setString("Player 2: " + std::to_string(rightScore));

    sf::FloatRect bounds = scoreTextRight.getLocalBounds();
    scoreTextRight.setOrigin(bounds.width, 0.f);
}

void UiMgr::SetFont(const sf::Font& f)
{
    font = const_cast<sf::Font*>(&f);
    scoreTextLeft.setFont(f);
    scoreTextRight.setFont(f);
}

void UiMgr::ShowRestartMessage(bool show)
{
    showRestartText = show;
}

void UiMgr::Init()
{   	
    scoreTextLeft.setFont(*font);
    scoreTextLeft.setCharacterSize(48);
    scoreTextLeft.setFillColor(sf::Color::White);
    scoreTextLeft.setPosition(20.f, 20.f);


    scoreTextRight.setFont(*font);
    scoreTextRight.setCharacterSize(48);
    scoreTextRight.setFillColor(sf::Color::White);
    scoreTextRight.setPosition(FRAMEWORK.GetWindowBounds().width - 20.f, 20.f);

    restartText.setFont(*font);
    restartText.setCharacterSize(36);
    restartText.setFillColor(sf::Color::White);
    restartText.setString("Press E to restart");

    sf::FloatRect bounds = restartText.getLocalBounds();
    restartText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    restartText.setPosition(FRAMEWORK.GetWindowBounds().width / 2.f, FRAMEWORK.GetWindowBounds().height / 2.f);
}

void UiMgr::Release()
{
}

void UiMgr::Reset()
{
}

void UiMgr::Update(float dt)
{
}

void UiMgr::Draw(sf::RenderWindow& window)
{
    window.draw(scoreTextLeft);
    window.draw(scoreTextRight);
    
    if (showRestartText)
    {
        window.draw(restartText);
    }    
}


