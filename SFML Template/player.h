#pragma once

class SceneGame;
class DebugBox;
class Item;
class UiHud;
class Anim;

class Player : public GameObject
{
protected:
	sf::Sprite body;
	std::string textureId = "graphics/player.png";

	int maxHp = 100;
	int hp;
	int ammo = 100;
	int clipSize;
	int clip;

	DebugBox debugbox;
	sf::Vector2f direction;
	sf::Vector2f look;

	float speed = 500.f;

	SceneGame* sceneGame;
	UiHud* uiHud;
	sf::RectangleShape reload;

	float shootTimer;
	float shootDelay = 0.5f;

	bool invincible;
	float invincibleTimer;
	float invincibleDelay = 0.5f;

	float reloadTimer;
	float reloadDelay = 0.5f;
	bool reloadFlag = true;

	sf::FloatRect moveableBounds;

	fz::Anim animIdle;
	fz::Anim animIdle2;


	sf::RectangleShape glaiveRect;
	float glaivesAngle;
public:
	Player(const std::string& name = "");
	~Player() = default;

	sf::Sprite& GetSprite() { return body; }

	void SetUiHud(UiHud* hud);

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt)override;
	void Draw(sf::RenderWindow& window) override;

	virtual sf::FloatRect GetLocalBounds() const
	{
		return body.getLocalBounds();
	}
	virtual sf::FloatRect GetGlobalBounds() const
	{
		return body.getGlobalBounds();
	}

	void OnItemGet(ItemTypes type, int amount);
	void OnDamage(int d);

	void ResetPos();

	void Shoot();

	void BufRateOfFire(float rate);
	void BufClipSize(int size);
	void BufMaxHp(int hp);
	void BufSpeed(float speed);


};
