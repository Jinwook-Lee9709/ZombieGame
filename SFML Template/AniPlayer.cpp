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
	std::string sheetId = "graphics/sprite_sheet.png";
	animator.SetSpeed(1.f);
	animator.SetTarget(&body);



	//idle.loadFromFile("Animation/idle.csv");
	//run.loadFromFile("Animation/run.csv");
	//jump.loadFromFile("Animation/jump.csv");

	/*{
		sf::IntRect coord(0, 0, 120, 120);
		idle.id = "Idle";
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
		jump.id = "Jump";
		jump.fps = 10;
		jump.loopType = AnimationLoopTypes::Single;
		for (int i = 0; i < 7; i++) {
			jump.frames.push_back(AnimationFrame(sheetId, coord));
			coord.left += 120;
		}
	}*/
	
}

void AniPlayer::Release()
{
}

void AniPlayer::Reset()
{
	animator.Play("Animation/idle.csv");
	SetOrigin(Origins::BC);
	SetPosition({ 0.f, 0.f });
}

void AniPlayer::Update(float dt)
{
	float h = 0.f;
	float v = InputMgr::GetAxis(Axis::Vertical);

	if (isGrounded) {
		h = InputMgr::GetAxis(Axis::Horizontal);
		velocity.x = speed * h;

	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		isGrounded = false;
		velocity.y = -250.f;
		animator.Play("Animation/jump.csv");
	}


	if (!isGrounded) {
		velocity += gravity * dt;
	}
	position += velocity * dt;
	if (position.y > 0.f) {
		position.y = 0.f;
		velocity.y = 0.f;
		isGrounded = true;
	}
	SetPosition(position);

	if (h != 0.f)
	{
		SetScale(h > 0.f ? sf::Vector2f{ 1.f, 1.f } : sf::Vector2f{ -1.f, 1.f });
	}
	if (animator.GetCurrentClipId() == "Idle")
	{
		if (h != 0.f)
		{
			animator.Play("Animation/run.csv");
		}
	}
	else if(animator.GetCurrentClipId() == "Run" ){
		if (h == 0.f)
		{
			animator.Play("Animation/idle.csv");
		}
	}
	else if (animator.GetCurrentClipId() == "Jump" && isGrounded) {
		if (h == 0.f)
		{
			animator.Play("Animation/idle.csv");
		}
		else {
			animator.Play("Animation/run.csv");
		}
	}
	animator.Update(dt);
}

void AniPlayer::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
