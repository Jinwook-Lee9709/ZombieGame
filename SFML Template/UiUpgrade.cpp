#include "stdafx.h"
#include "UiUpgrade.h"
#include "Player.h"
#include "ItemManager.h"
#include "SceneGame.h"

UiUpgrade::UiUpgrade(const std::string& name)
	: GameObject(name)
{
}

void UiUpgrade::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void UiUpgrade::SetRotation(float angle)
{
	rotation = angle;
}

void UiUpgrade::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void UiUpgrade::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void UiUpgrade::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void UiUpgrade::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;
	float textSize = 80.f;
	sf::Font& font = FONT_MGR.Get("fonts/zombiecontrol.ttf");
	sf::Vector2f pos({ 300.f, 200.f });
	for (int i = 0; i < 6; i++) {
		sf::Text temp;
		text.push_back(temp);
	}
	text[0].setString("1- INCREASED RATE OF FIRE");
	text[1].setString("2- INCREASED CLIP SIZE(NEXT RELOAD)");
	text[2].setString("3- INCREASED MAXM HEALTH");
	text[3].setString("4- INCREASED RUN SPEED");
	text[4].setString("5- MORE AND BETTER HEALTH PICKUPS");
	text[5].setString("6- MORE AND BETTER AMMO PICUPS");
	for (auto& it : text) {
		it.setFont(font);
		it.setPosition(pos);
		it.setCharacterSize(textSize);
		it.setFillColor(sf::Color::White);
		pos.y += 100;
	}
	background.setTexture(TEXTURE_MGR.Get("graphics/background.png"));
}

void UiUpgrade::Release()
{
}

void UiUpgrade::Reset()
{
}

void UiUpgrade::Update(float dt)
{
	CheckTextClick();
}

void UiUpgrade::Draw(sf::RenderWindow& window)
{
	if (active == true)
	{
		window.draw(background);
		for (auto it : text)
		{
			window.draw(it);
		}
	}
	
}

void UiUpgrade::SetPlayer(Player* player)
{
	this->player = player;
}

void UiUpgrade::SetItemManager(ItemManager* mgr)
{
	this->itemManager = mgr;
}


void UiUpgrade::CheckTextClick()
{
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	if (sceneGame != nullptr) {
		sf::Vector2f mousePos = sceneGame->ScreenToUi(InputMgr::GetMousePosition());
		Types clickedText = Types::NONE;
		for (int i = 0; i < 6; i++) {
			if (text[i].getGlobalBounds().contains(mousePos)) {
				text[i].setFillColor(sf::Color::Red);
				if (InputMgr::GetMouseButtonDown(sf::Mouse::Left)) {
					clickedText = (Types)i;
				}
			}
			else {
				text[i].setFillColor(sf::Color::White);
			}
		}
		std::cout << (int)clickedText;
		switch (clickedText) {
		case Types::RATEOFFIRE:
			player->BufRateOfFire(0.05f);
			break;
		case Types::CLIPSIZE:
			player->BufClipSize(3);
			break;
		case Types::MAXHEALTH:
			player->BufMaxHp(20);
			break;
		case Types::RUNSPEED:
			player->BufSpeed(20);
			break;
		case Types::HEALTHPICKUP:
			itemManager->BufMedRegen(1);
			break;
		case Types::AMMOPICKUP:
			itemManager->BufAmmoRegen(1);
			break;
		}
		if (clickedText != Types::NONE) {
			sceneGame->BufSelected();
		}
	}
	
}
