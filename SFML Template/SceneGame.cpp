#include "stdafx.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"
#include "Bullet.h"
#include "ItemManager.h"
#include "UiHud.h"
#include "UiUpgrade.h"
#include "UiGameOver.h"

SceneGame::SceneGame()
	: Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	map = AddGo(new TileMap("TileMap"));
	player = AddGo(new Player("Player"));
	uiHud = AddGo(new UiHud("UiHud"));
	uiUpgrade = AddGo(new UiUpgrade("UiUpgrade"));
	uiGameOver = AddGo(new UiGameOver("UiGameOver"));
	itemManager = AddGo(new ItemManager("ItemManager"));
	Scene::Init();
}

void SceneGame::Release()
{
	Scene::Release();
}

void SceneGame::Enter()
{
	waveStart = true;
	currentState = State::PLAY;
	FRAMEWORK.GetWindow().setMouseCursorVisible(false);
	cursor.setTexture(TEXTURE_MGR.Get("graphics/crosshair.png"));
	Utils::SetOrigin(cursor, Origins::MC);

	score = 0;
	wave = 1;

	uiHud->SetWave(wave);
	uiGameOver->SetActive(false);
	uiUpgrade->SetActive(false);
	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(size);
	worldView.setCenter(0.f, 0.f);

	uiView.setSize(size);
	uiView.setCenter(size.x * 0.5f, size.y * 0.5f);
	itemManager->SetActive(true);

	/*area.SetPosition(0.0f, 0.0f);
	area.SetSize(500.f, 500.f);
	area.SetOrigin(Origins::TL);
	area.SetDrawable(true);
	area.SetOutlineColor(sf::Color::Blue);
	area.SetOutlineThickness(30.f);*/

	//Set Reference
	uiUpgrade->SetPlayer(player);
	uiUpgrade->SetItemManager(itemManager);

	player->SetUiHud(uiHud);
	Scene::Enter();
}

void SceneGame::Exit()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(true);
	for (auto zombie : zombies) {
		RemoveGo(zombie);
		zombiePool.Return(zombie);
	}
	zombies.clear();
	

	for (auto bullet : bullets) {
		RemoveGo(bullet);
		bulletPool.Return(bullet);
	}
	bullets.clear();
	Scene::Exit();
}

void SceneGame::Reset()
{
	score = 0;
	wave = 1;
	waveStart = true;
	beforeState = State::None;
	currentState = State::PLAY;


	player->Reset();
	for (auto zombie : zombies) {
		RemoveGo(zombie);
		zombiePool.Return(zombie);
	}
	zombies.clear();

	for (auto bullet : bullets) {
		RemoveGo(bullet);
		bulletPool.Return(bullet);
	}
	bullets.clear();

	uiGameOver->SetActive(false);
	uiUpgrade->SetActive(false);
	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(size);
	worldView.setCenter(0.f, 0.f);

	uiView.setSize(size);
	uiView.setCenter(size.x * 0.5f, size.y * 0.5f);
	itemManager->ResetSpawn();
	itemManager->SetSpawn(true);

	uiHud->SetWave(wave);

}

void SceneGame::Update(float dt)
{
	sf::Vector2f mousePos = ScreenToUi(InputMgr::GetMousePosition());
	cursor.setPosition(mousePos);
	Scene::Update(dt);


	if (player != nullptr)
	{
		worldView.setCenter(player->GetPosition());
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Space)) {
		Spawn(100);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num1)) {
		uiUpgrade->SetActive(false);
	}

	switch(currentState) {
		case State::PLAY: {
			if (beforeState == State::UPGRADE) {
				uiHud->SetWave(wave);
				waveStart = true;
				bufSelected = false;
				uiUpgrade->SetActive(false);
				beforeState = State::None;
			}
			UpdatePlay(dt);
			break;
		}
		case State::GAMEOVER: {
			UpdateGameover(dt);
			break;
		}
		case State::UPGRADE: {
			if (beforeState == State::PLAY) {
				bufSelected = false;
				uiUpgrade->SetActive(true);
				beforeState = State::None;
			}
			if (bufSelected == true) {
				bufSelected = false;
				uiUpgrade->SetActive(false);
				player->ResetPos();
				itemManager->ResetSpawn();
				beforeState = State::UPGRADE;
				currentState = State::PLAY;
			}
			UpdateUpgrade(dt);
			break;
		}
	}

}
void SceneGame::UpdatePlay(float dt)
{
	if (waveStart == true) {
		Spawn(10 + 5 * wave);
		waveStart = false;
	}
	uiHud->SetScore(score);
	uiHud->SetZombieCount(zombies.size());
	if (zombies.size() == 0) {
		beforeState = State::PLAY;
		currentState = State::UPGRADE;
	}
}

void SceneGame::UpdateGameover(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter)) {
		Reset();
	}
}

void SceneGame::UpdateUpgrade(float dt)
{
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	//area.Draw(window);
	Scene::Draw(window);
	const sf::View& saveView = window.getView();
	window.setView(uiView);
	window.draw(cursor);
	window.setView(saveView);
}



void SceneGame::BufSelected()
{
	bufSelected = true;
}

sf::Vector2f SceneGame::GetSpawnPos()
{
	sf::FloatRect bounds = map->GetGlobalBounds();
	sf::Vector2f pos;
	pos = Utils::RandomOnUnitCircle();
	pos = pos * Utils::RandomRange(bounds.width * 0.3f, bounds.width * 0.4f);
	//if (Utils::RandomRange(0, 1) == 0) {
	//	pos = {
	//		bounds.left + Utils::RandomRange(0.f, range.x),
	//		bounds.top + Utils::RandomRange(0.f, range.y)
	//	};
	//}
	//else {
	//	pos = {
	//	bounds.left + bounds.width - Utils::RandomRange(0.f, range.x),
	//	bounds.top + bounds.height - Utils::RandomRange(0.f, range.y)
	//	};
	//}
	return pos;
}

void SceneGame::Spawn(int count)
{
	for (int i = 0; i < count; i++) {
		auto obj = AddGo(zombiePool.Take());
		zombies.push_back(obj);
		Zombie::Types type = (Zombie::Types)Utils::RandomRange(0, (int)Zombie::Types::Count-1);
		obj->Set(type);

		sf::Vector2f pos = GetSpawnPos();
		obj->SetPosition(pos);
	}

}

Bullet* SceneGame::TakeBullet()
{
	Bullet* bullet = bulletPool.Take();
	bullets.push_back(bullet);
	AddGo(bullet);
	return bullet;
}

sf::FloatRect SceneGame::GetTileBounds()
{
	return map->GetGlobalBounds();
}

sf::FloatRect SceneGame::GetMoveableBounds()
{
	return map->GetMoveableBounds();
}

void SceneGame::ReturnBullet(Bullet* bullet)
{
	RemoveGo(bullet);
	bulletPool.Return(bullet);
	bullets.remove(bullet);
}

void SceneGame::OnPlayerDie()
{
	currentState = State::GAMEOVER;
	uiGameOver->SetActive(true);
	itemManager->SetSpawn(false);
}

void SceneGame::OnZombieDie(Zombie* zombie)
{
	RemoveGo(zombie);
	zombiePool.Return(zombie);
	zombies.remove(zombie);
}

void SceneGame::OnGetScore()
{
	score += 50;
}

