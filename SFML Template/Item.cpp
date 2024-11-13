#include "stdafx.h"
#include "Item.h"
#include "Player.h"
#include "ItemManager.h"
#include "ItemTable.h"

Item::Item(const std::string& name, const std::string& textureId)
	: GameObject(name), textureId(textureId)
{
}

void Item::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Item::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Item::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Item::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, preset);
	}
}

void Item::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Item::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 3;
	textureId = "graphics/ammo_pickup.png";
}

void Item::Release()
{
	
}

void Item::Reset()
{
	body.setTexture(TEXTURE_MGR.Get(textureId));
	player = (Player*)SCENE_MGR.GetCurrentScene()->FindGo("Player");
}

void Item::Update(float dt)
{

	
}

void Item::FixedUpdate(float dt)
{
	if (player != nullptr && Utils::CheckCollision(player->GetSprite(), body))
	{
		switch (type) {
			case ItemTypes::Ammo: {
				player->OnItemGet(type, 100);
			}
			case ItemTypes::Medkit: {
				player->OnItemGet(type, 50);
			}
		}
		itemManager->OnItemUsed(this);
	
	}
}

void Item::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Item::SetItemManager(ItemManager* address)
{
	itemManager = address;
}

void Item::Set(ItemTypes type)
{
	this->type = type;
	textureId = ITEM_TABLE->Get(type).textureId;
	amount = ITEM_TABLE->Get(type).amount;
	body.setTexture(TEXTURE_MGR.Get(textureId), true);
}
