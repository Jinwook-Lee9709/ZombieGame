#include "stdafx.h"
#include "UiGameOver.h"

UiGameOver::UiGameOver(const std::string& name)
	: GameObject(name)
{
}

void UiGameOver::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void UiGameOver::SetRotation(float angle)
{
	rotation = angle;
}

void UiGameOver::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void UiGameOver::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void UiGameOver::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void UiGameOver::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;
	float textSize = 150.f;
	sf::Font& font = FONT_MGR.Get("fonts/zombiecontrol.ttf");
	sf::Vector2f pos = 0.5f * FRAMEWORK.GetWindowSizeF();
	text.setString("PRESS ENTER \n TO COTINUE");
	text.setFont(font);
	text.setPosition(pos);
	text.setCharacterSize(textSize);
	text.setFillColor(sf::Color::White);
	Utils::SetOrigin(text, Origins::MC);



}

void UiGameOver::Release()
{
}

void UiGameOver::Reset()
{
	sf::Font& font = FONT_MGR.Get("fonts/zombiecontrol.ttf");
	text.setFont(font);
}

void UiGameOver::Update(float dt)
{
}

void UiGameOver::Draw(sf::RenderWindow& window)
{
	if (active == true)
	{
		window.draw(text);
	}
	
}
