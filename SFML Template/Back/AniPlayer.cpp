#include "stdafx.h"
#include "AniPlayer.h"

AniPlayer::AniPlayer(const std::string& name)
	: GameObject(name)
{
}

void AniPlayer::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void AniPlayer::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(angle);
}

void AniPlayer::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void AniPlayer::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void AniPlayer::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void AniPlayer::Init()
{
	animator.SetTarget(&body);
	std::string sheetId = "graphics/sprite_sheet.png";
	{
		sf::IntRect coord(0, 0, 120, 120);
		idle.id = "Idel";
		idle.fps = 10;
		idle.loopType = AnimationLoopTypes::Loop;
		for (int i = 0; i < 8; i++) 
		{
			idle.frames.push_back(AnimationFrame(sheetId, coord));
			coord.left = 120 * i;
		}
		
	}
	{
		sf::IntRect coord(0, 120, 120, 120);
		run.id = "Run";
		run.fps = 10;
		run.loopType = AnimationLoopTypes::Loop;
		for (int i = 0; i < 8; i++) {
			run.frames.push_back(AnimationFrame(sheetId, coord));
			coord.left += 120;
			if (coord.left == TEXTURE_MGR.Get(sheetId).getSize().x) {
				coord.top += 120;
				coord.left = 0;
			}
		}
	}
	{
		sf::IntRect coord(0, 360, 120, 120);
		jump.id = "jump";
		jump.fps = 10;
		jump.loopType = AnimationLoopTypes::Single;
		for (int i = 0; i < 7; i++) {
			jump.frames.push_back(AnimationFrame(sheetId, coord));
			coord.left += 120;
		}
	}
	
}

void AniPlayer::Release()
{
}

void AniPlayer::Reset()
{
	animator.Play(&idle);
	SetOrigin(Origins::BC);
	SetPosition({ 300.f, 300.f });
}

void AniPlayer::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::A) || InputMgr::GetKeyDown(sf::Keyboard::D))
	{
		animator.Play(&run);
	}
	if (InputMgr::GetKeyUp(sf::Keyboard::A) || InputMgr::GetKeyUp(sf::Keyboard::D))
	{
		animator.Play(&idle);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::W))
	{
		animator.Play(&jump);
	}
	sf::Vector2f axis = {InputMgr::GetAxis(Axis::Horizontal), InputMgr::GetAxis(Axis::Vertical)};
	if (axis.x > 0) {
		
	}
	position += {axis.x * speed * dt, 0};
	SetPosition(position);
	animator.Update(dt);
}

void AniPlayer::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
