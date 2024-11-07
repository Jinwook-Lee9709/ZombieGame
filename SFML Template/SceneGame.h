#pragma once
#include "Scene.h"
#include "SpawnArea.hpp"

class Player;
class Zombie;
class TileMap;
class Bullet;
class ItemManager;
class UiHud;
class UiUpgrade;
class UiGameOver;

class SceneGame : public Scene
{
public:
	enum class State {
		None = -1,
		PLAY,
		GAMEOVER,
		UPGRADE
	};

protected:
	State beforeState;
	State currentState;

	int score;
	int wave;
	bool waveStart;
	bool bufSelected;
	sf::Sprite cursor;

	Player* player;
	TileMap* map;
	UiHud* uiHud;
	UiUpgrade* uiUpgrade;
	UiGameOver* uiGameOver;

	ItemManager* itemManager;

	ObjectPool<Zombie> zombiePool;
	std::list<Zombie*> zombies;
	
	std::list<Bullet*> bullets;
	ObjectPool<Bullet> bulletPool;

	SpawnArea area;

public:
	SceneGame();
	virtual ~SceneGame() = default;

	void Init();
	void Release();
	void Enter();
	void Exit();
	void Reset();
	void Update(float dt);
	void UpdatePlay(float dt);
	void UpdateGameover(float dt);
	void UpdateUpgrade(float dt);
	void Draw(sf::RenderWindow& window) override;


	void BufSelected();

	sf::Vector2f GetSpawnPos();
	void Spawn(int count);

	Bullet* TakeBullet();
	sf::FloatRect GetTileBounds();
	sf::FloatRect GetMoveableBounds();
	void ReturnBullet(Bullet* bullet);

	const std::list<Zombie*>& GetZombieList() const { return zombies;  }

	void OnPlayerDie();
	void OnZombieDie(Zombie* zombie);
	void OnGetScore();

};

