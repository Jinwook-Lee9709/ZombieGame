#include "stdafx.h"
#include "UiGameOver.h"

UiGameOver::UiGameOver(const std::string& name)
	: GameObject(name), text("")
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
	sf::Vector2f pos = 0.5f * FRAMEWORK.GetWindowSizeF();
	text = TextGo("fonts/BMJUA.ttf");
	text.SetString("ContinueText");
	text.SetPosition(pos);
	text.SetCharacterSize(textSize);
	text.SetFillColor(sf::Color::White);
	text.SetOrigin(Origins::MC);



}

void UiGameOver::Release()
{
}

void UiGameOver::Reset()
{
	text.SetFont("fonts/BMJUA.ttf");
}

void UiGameOver::Update(float dt)
{
}

void UiGameOver::Draw(sf::RenderWindow& window)
{
	if (active == true)
	{
		text.Draw(window);
	}
	
}

void UiGameOver::OnLocalize(Languages lang)
{
	text.OnLocalize(lang);
}
