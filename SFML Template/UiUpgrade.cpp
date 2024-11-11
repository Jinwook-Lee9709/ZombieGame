#include "stdafx.h"
#include "UiUpgrade.h"
#include "Player.h"
#include "ItemManager.h"
#include "SceneGame.h"
#include "TextGo.h"

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
	sf::Vector2f pos({ 300.f, 200.f });
	for (int i = 0; i < 6; i++) {
		TextGo temp("fonts/BMJUA.ttf");
		text.push_back(temp);
	}
	text[0].SetString("Upgrade1");
	text[1].SetString("Upgrade2");
	text[2].SetString("Upgrade3");
	text[3].SetString("Upgrade4");
	text[4].SetString("Upgrade5");
	text[5].SetString("Upgrade6");
	for (auto& it : text) {
		it.SetPosition(pos);
		it.SetCharacterSize(textSize);
		it.SetFillColor(sf::Color::White);
		pos.y += 100;
	}
	background.setTexture(TEXTURE_MGR.Get("graphics/background.png"));
}

void UiUpgrade::Release()
{
}

void UiUpgrade::Reset()
{
	for (int i = 0; i < 6; i++) {
		text[i].Reset();
	}
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
			it.Draw(window);
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

void UiUpgrade::OnLocalize(Languages Lang)
{
	for (auto& it : text) {
		it.OnLocalize(Lang);
	}
}


void UiUpgrade::CheckTextClick()
{
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	if (sceneGame != nullptr) {
		sf::Vector2f mousePos = sceneGame->ScreenToUi(InputMgr::GetMousePosition());
		Types clickedText = Types::NONE;
		for (int i = 0; i < 6; i++) {
			if (text[i].GetGlobalBounds().contains(mousePos)) {
				text[i].SetFillColor(sf::Color::Red);
				if (InputMgr::GetMouseButtonDown(sf::Mouse::Left)) {
					clickedText = (Types)i;
				}
			}
			else {
				text[i].SetFillColor(sf::Color::White);
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
