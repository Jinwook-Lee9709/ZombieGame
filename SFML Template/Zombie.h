#pragma once

class Player;
class SceneGame;
class DebugBox;
class Zombie : public GameObject
{
public:
	enum class Types
	{
		Bloater,
		Chaser,
		Crawler,
		Count
	};
	enum class State
	{
		None = -1,
		Die,
		Alive
	};
protected:
	sf::Sprite body;
	sf::RectangleShape hpBox;
	sf::RectangleShape hpBoxFrame;
	std::string textureId = "graphics/bloater.png";
	std::string textureIdBlood = "graphics/blood.png";
	sf::Vector2f direction;
	int maxHp;
	int damage;
	float speed;
	int hp;

	Types type = Types::Bloater;	

	State beforeState = State::None;
	State currentState = State::Alive;

	Player* player;
	SceneGame* sceneGame = nullptr;

	float attackTimer;
	float attackInterval;

	float bloodTimer;
	float bloodDuration = 3.f;

	float glaiveTimer;
	float glaiveDuration = 0.05f;

public:
	Zombie(const std::string& name = "");
	~Zombie() = default;

	sf::Sprite& GetSprite() { return body; }

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	sf::FloatRect GetLocalBounds() const override;
	sf::FloatRect GetGlobalBounds() const override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void UpdateAlive(float dt);
	void UpdateDie(float dt);
	void FixedUpdate(float dt) override;
	void FixedUpdateAlive(float dt);
	void FixedUpdateDie(float dt);
	void Draw(sf::RenderWindow& window) override;

	void Set(Types type);

	bool IsAlive() { return (bool)currentState; }
	void OnDamage(int damage);
	void OnGlaiveDamage(int d);
};
