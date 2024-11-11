#include "stdafx.h"
#include "Player.h"
#include "SceneGame.h"
#include "Bullet.h"
#include "DebugBox.h"
#include "UiHud.h"
#include "Zombie.h"

Player::Player(const std::string& name)
	: GameObject(name)
{

}

void Player::SetUiHud(UiHud* hud)
{
	uiHud = hud;
}

void Player::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Player::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(angle);
}

void Player::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(s);
}

void Player::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Player::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Player::Init()
{
	animIdle.LoadFromFile("graphics/Glaives/Glaives_Sheet.png");
	animIdle2.LoadFromFile("graphics/Glaives/GlaivesShadow_Sheet.png");

	animIdle.SetAnimSequence(
		{ 0, 0, 602, 406 },                     // 프레임의 x, y, width, height
		0, 0.05f, 26);
	animIdle2.SetAnimSequence(
		{ 0, 0, 602, 406 },                     // 프레임의 x, y, width, height
		0, 0.05f, 26);
	animIdle.SetScale(0.5f, 0.5f);
	animIdle2.SetScale(0.5f, 0.5f);
	animIdle.SetPosition(position - sf::Vector2f{ 301.f, 203.f });
	animIdle2.SetPosition(position - sf::Vector2f{ 301.f, 203.f });
	glaiveRect.setSize({ 602, 406 });
	glaiveRect.setScale({ 0.31f, 0.31f });
	glaiveRect.setFillColor(sf::Color::Red);

	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

	SetOrigin(Origins::MC);
}

void Player::Release()
{
}

void Player::Reset()
{
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	hp = maxHp = 5;
	clip = clipSize = 7;
	ammo = 50;
	reloadTimer = 0;

	invincible = false;

	moveableBounds = sceneGame->GetMoveableBounds();
	body.setTexture(TEXTURE_MGR.Get(textureId), true);
	sword.setTexture(TEXTURE_MGR.Get("graphics/sword.png"), true);
	sword.setScale({ 0.2f, 0.2f });
	Utils::SetOrigin(sword, Origins::MC);
	SetOrigin(originPreset);
	SetPosition({ 0.f, 0.f });
	SetRotation(0.f);
	direction = { 1.f, 0.f };
}

void Player::Update(float dt)
{
	animIdle.Update(dt);
	animIdle2.Update(dt);
	if (hp == 0) {
		return;
	}
	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);
	float mag = Utils::Magnitude(direction);
	if (mag > 1.f)
	{
		Utils::Normalize(direction);
	}

	sf::Vector2i mousePos = InputMgr::GetMousePosition();
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(mousePos);
	look = Utils::GetNormal(mouseWorldPos - position);

	SetRotation(Utils::Angle(look));
	sf::Vector2f newPos = position + direction * speed * dt;
	if (moveableBounds.contains(newPos)) {
		SetPosition(position + direction * speed * dt);
	}

	shootTimer += dt;
	if (shootTimer > shootDelay && InputMgr::GetMouseButton(sf::Mouse::Left))
	{
		shootTimer = 0.f;
		Shoot();
	}

	sf::FloatRect bounds = body.getLocalBounds();
	bounds.left += body.getPosition().x;
	bounds.top += body.getPosition().y;
	debugbox.SetRotateBounds(bounds, rotation);

	if (InputMgr::GetKeyDown(sf::Keyboard::R)) {
		if (reloadFlag == true && clip != clipSize) {
			reloadFlag = false;
			reload.setFillColor(sf::Color::Yellow);
			reload.setSize({ (float)body.getTextureRect().width, 10.f });
			reload.setScale({ 0.f, 1.f });
		}
	}
	if (reloadFlag == false) {
		reloadTimer += dt;
		reload.setPosition({ position.x - body.getTextureRect().width * 0.5f, position.y - body.getTextureRect().height });
		reload.setScale(reloadTimer / reloadDelay, 1.f);
		if (reloadTimer > reloadDelay) {
			if (clipSize > ammo) {
				clip = ammo;
				ammo = 0;
			}
			else {
				clip = clipSize;
				ammo -= clipSize;
			}
			reloadTimer = 0;
			reloadFlag = true;
			reload.setFillColor(sf::Color::Transparent);
		}
	}
	if (invincible == true) {
		invincibleTimer += dt;
		if (invincibleDelay < invincibleTimer) {
			invincible = false;
			body.setColor(sf::Color::White);
		}
	}
	glaivesAngle += 2.f * dt;
	sf::Vector2f pos = { position.x - 150.f + 150 * cosf(glaivesAngle), position.y - 100.f + 150 * sinf(glaivesAngle) };
	animIdle.SetPosition(pos);
	animIdle2.SetPosition(pos);
	glaiveRect.setPosition(pos + sf::Vector2f{ 50.f,35.f });

	const auto& list = sceneGame->GetZombieList();
	if (targeted == false) {
		Zombie* closetsZombie = nullptr;
		float distance;
		if (list.size() != 0) {
			distance = std::numeric_limits<float>::max();
			for (auto zombie : list) {
				if (!zombie->IsAlive()) {
					continue;
				}
				float temp_distance = Utils::Distance(position, zombie->GetPosition());
				if (temp_distance < distance)
				{
					distance = temp_distance;
					closetsZombie = zombie;
				}

			}
			if (closetsZombie != nullptr)
			{
				targetedZombie = closetsZombie;
				targeted = true;
			}
		}
	}
	sf::Vector2f swordPos = sword.getPosition();
	if (std::find(list.begin(), list.end(), targetedZombie) != list.end() && targetedZombie->IsAlive()) {
		sf::Vector2f zombiePos = targetedZombie->GetPosition();
		direction = Utils::GetNormal(zombiePos - swordPos);
		sword_direction = Utils::Lerp(sword_direction, direction, dt * 3.f);
		Utils::Normalize(sword_direction);
		//std::cout << sword_direction << std::endl;
		swordPos += sword_direction * speed * dt;
		sword.setRotation(Utils::Angle(sword_direction) + 90.f);
		sword.setPosition(swordPos);
	}
	else {
		targeted = false;
	}
}

void Player::FixedUpdate(float dt)
{
	if (hp == 0) {
		sceneGame->OnPlayerDie();
	}
	uiHud->SetHp(hp, maxHp);
	uiHud->SetAmmo(clip, ammo);
	const auto& list = sceneGame->GetZombieList();
	for (auto zombie : list) {
		if ((glaiveRect.getGlobalBounds().intersects(zombie->GetGlobalBounds()))) {
			zombie->OnGlaiveDamage(2);
		}
	}
	if (targetedZombie != nullptr && targetedZombie->IsAlive()) {
		if ((sword.getGlobalBounds().intersects(targetedZombie->GetGlobalBounds()))) {
			targetedZombie->OnDamage(200);
			targeted = false;
		}
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	window.draw(reload);
	window.draw(sword);
	animIdle2.Draw(window);
	animIdle.Draw(window);

	debugbox.Draw(window);
}

void Player::OnItemGet(ItemTypes type, int amount)
{
	switch (type)
	{
	case ItemTypes::Ammo:
		ammo += amount;
		break;
	case ItemTypes::Medkit:
		hp = Utils::Clamp(hp += amount, 0, maxHp);
		break;
	}
}

void Player::OnDamage(int d)
{
	if (invincible == false) {
		hp = Utils::Clamp(hp - d, 0, maxHp);
		invincible = true;
		invincibleTimer = 0;
		body.setColor(sf::Color(150, 150, 150, 255));
	}

}

void Player::ResetPos()
{
	SetPosition({ 0.f, 0.f });
}

void Player::Shoot()
{
	if (clip > 0) {
		Bullet* bullet = sceneGame->TakeBullet();
		bullet->Fire(position, look, 500.f, 10);
		clip--;
	}
}

void Player::BufRateOfFire(float rate)
{
	if (shootDelay > 0.05f) {
		shootDelay -= rate;
	}
}

void Player::BufClipSize(int size)
{
	clipSize += size;
}

void Player::BufMaxHp(int hp)
{
	maxHp += hp;
}

void Player::BufSpeed(float speed)
{
	this->speed += speed;
}
