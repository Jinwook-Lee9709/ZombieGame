#pragma once

class Player;
class ItemManager;
class Item : public GameObject
{
public:
	enum class RecoveryType {
		HEAL,
		RESUPPLY
	};
protected:
	sf::Sprite body;
	std::string textureId;
	Player* player;

	int amount;

	ItemTypes type;

	ItemManager* itemManager;
public:
	Item(const std::string& name = "", const std::string& textureId = "");
	~Item() = default;

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

	void SetItemManager(ItemManager* address);
	void Set(ItemTypes type);
};
