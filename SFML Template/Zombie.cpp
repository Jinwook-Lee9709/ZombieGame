#pragma once
#include "stdafx.h"
#include "Zombie.h"
#include "Player.h"
#include "SceneGame.h"
#include "DebugBox.h"

Zombie::Zombie(const std::string& name)
	: GameObject(name)
{
}

void Zombie::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
	hpBox.setPosition(position -sf::Vector2f {30.f, body.getLocalBounds().height * 0.6f});
	hpBoxFrame.setPosition(position - sf::Vector2f{ 30.f, body.getLocalBounds().height * 0.6f });
}

void Zombie::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Zombie::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Zombie::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Zombie::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

sf::FloatRect Zombie::GetLocalBounds() const
{
	return body.getLocalBounds();
}

sf::FloatRect Zombie::GetGlobalBounds() const
{
	return body.getGlobalBounds();
}

void Zombie::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;

	Set(type);
}

void Zombie::Release()
{
}

void Zombie::Reset()
{
	sceneGame = (SceneGame*)(SCENE_MGR.GetCurrentScene());
	beforeState = State::None;
	currentState = State::Alive;
	hpBox.setSize({ 60.f, 10.f });
	hpBox.setFillColor(sf::Color::Red);
	hpBoxFrame.setSize({ 60.f, 10.f });
	hpBoxFrame.setFillColor(sf::Color::Transparent);
	hpBoxFrame.setOutlineThickness(2);
	hpBoxFrame.setOutlineColor(sf::Color::Black);
	bloodTimer = 0;
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
	body.setTexture(TEXTURE_MGR.Get(textureId));
	SetPosition({ 0.f, 0.f });
	SetScale(scale);
	SetOrigin(Origins::MC);
	
	

	attackTimer = 0;

}

void Zombie::Update(float dt)
{
	switch (currentState)
	{
		case State::Alive: {
			UpdateAlive(dt);
			break;
			}
		case State::Die: {
			UpdateDie(dt);
			break;
		}
	}


}
void Zombie::UpdateAlive(float dt)
{
	sf::Vector2f playerPos = player->GetPosition();
	direction = Utils::GetNormal(playerPos - position);
	if (player != nullptr && Utils::Distance(playerPos, position) > 20.f) {
		position += direction * speed * dt;
		SetRotation(Utils::Angle(direction));
		SetPosition(position);
	}
}
void Zombie::UpdateDie(float dt)
{
}
void Zombie::FixedUpdate(float dt)
{
	switch (currentState)
	{
		case State::Alive: {
			FixedUpdateAlive(dt);
			break;
		}
		case State::Die: {
			if (beforeState == State::Alive) {
				hpBoxFrame.setOutlineColor(sf::Color::Transparent);
				hpBox.setOutlineColor(sf::Color::Transparent);
				bloodTimer = 0;
				body.setTexture(TEXTURE_MGR.Get(textureIdBlood));
				sortingOrder = -2;
				beforeState = State::None;
			}
			FixedUpdateDie(dt);
			break;
		}
	}
	hpBox.setScale((float)hp / maxHp, 1.f);
}

void Zombie::FixedUpdateAlive(float dt)
{
	attackTimer += dt;
	glaiveTimer += dt;
	sf::Sprite playerSprite = player->GetSprite();
	if (attackTimer > attackInterval && Utils::CheckCollision(body, playerSprite))
	{
		player->OnDamage(damage);
		attackTimer = 0;
	}
}

void Zombie::FixedUpdateDie(float dt)
{
	bloodTimer += dt;
	if (sceneGame != nullptr && bloodTimer > bloodDuration) {
		sceneGame->OnZombieDie(this);
	}
}

void Zombie::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	window.draw(hpBox);
	window.draw(hpBoxFrame);
}

void Zombie::Set(Types type)
{
	switch (type)
	{ 
	case Types::Bloater:
		textureId = "graphics/bloater.png";
		maxHp = 50;
		speed = 100.f;
		damage = 10;
		this->type = type;
		break;
	case Types::Chaser:
		textureId = "graphics/chaser.png";
		maxHp = 20;
		speed = 100.f;
		this->type = type;
		damage = 5;
		break;
	case Types::Crawler:
		textureId = "graphics/Crawler.png";
		maxHp = 10;
		speed = 60.f;
		this->type = type;
		damage = 10;
		break;
	}
	hp = maxHp;
	body.setTexture(TEXTURE_MGR.Get(textureId));
}

void Zombie::OnDamage(int d)
{
	hp -= d;
	if (hp <= 0 && sceneGame != nullptr)
	{
		beforeState = State::Alive;
		currentState = State::Die;		
		sceneGame->OnGetScore();
	}

}

void Zombie::OnGlaiveDamage(int d)
{
	if (glaiveTimer > glaiveDuration) {
		hp -= d;
		if (hp <= 0 && sceneGame != nullptr)
		{
			beforeState = State::Alive;
			currentState = State::Die;
			sceneGame->OnGetScore();
		}
		glaiveTimer = 0;
	}
	

}
