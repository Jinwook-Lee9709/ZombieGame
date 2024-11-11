#pragma once
#pragma once

class Player;
class ItemManager;
class TextGo;

class UiUpgrade : public GameObject
{
public:
	enum class Types
	{
		NONE = -1,
		RATEOFFIRE,
		CLIPSIZE,
		MAXHEALTH,
		RUNSPEED,
		HEALTHPICKUP,
		AMMOPICKUP
	};

protected:
	sf::Sprite background;
	std::vector<TextGo> text;


	Player* player;
	ItemManager* itemManager;
public:
	UiUpgrade(const std::string& name = "");
	~UiUpgrade() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetPlayer(Player* player);
	void SetItemManager(ItemManager* mgr);
	void OnLocalize(Languages Lang) override;

	void CheckTextClick();
};
