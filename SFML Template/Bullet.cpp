#include "stdafx.h"
#include "Bullet.h"
#include "SceneGame.h"
#include "Zombie.h"

Bullet::Bullet(const std::string& name)
	: GameObject(name)
{
}

void Bullet::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Bullet::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Bullet::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Bullet::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Bullet::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

sf::FloatRect Bullet::GetLocalBounds() const
{
	return body.getLocalBounds();
}

sf::FloatRect Bullet::GetGlobalBounds() const
{
	return body.getGlobalBounds();
}

void Bullet::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
}

void Bullet::Release()
{
}

void Bullet::Reset()
{
	sceneGame = (SceneGame*)(SCENE_MGR.GetCurrentScene());

	body.setTexture(TEXTURE_MGR.Get(textureId));
	SetOrigin(Origins::ML);

	SetPosition({ 0.f, 0.f });
	SetRotation(0.f);
	SetScale({ 1.f, 1.f });

	direction = { 0.f, 0.f };
	speed = 0;
	damage = 0;
}

void Bullet::Update(float dt)
{
	SetPosition(position + direction * speed * dt);
	debugBox.SetBounds(GetGlobalBounds());
}

void Bullet::FixedUpdate(float dt)
{
	if (sceneGame == nullptr)
		return;
	const auto& list = sceneGame->GetZombieList();
	debugBox.SetOutlineColor(sf::Color::Green);
	for (auto zombie : list)
	{
		if (!zombie->IsActive() || !zombie->IsAlive())
			continue;
		sf::Sprite zombieSprte = zombie->GetSprite();
		if (Utils::CheckCollision(body,zombieSprte))
		{
			debugBox.SetOutlineColor(sf::Color::Red);
			zombie->OnDamage(damage);
			sceneGame->ReturnBullet(this);
			break;
		}

	}
}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	debugBox.Draw(window);
}

void Bullet::Fire(const sf::Vector2f& pos, const sf::Vector2f& dir, float s, int d)
{
	
	SetPosition(pos);
	direction = dir;
	speed = s;
	damage = d;

	SetRotation(Utils::Angle(direction));
	
	/*SOUND_MGR.PlaySfx(SOUNDBUFFER_MGR.Get("sound/shoot.wav"), false);*/
}
