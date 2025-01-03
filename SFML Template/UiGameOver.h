#pragma once
#pragma once

class TextGo;
class UiGameOver : public GameObject
{
protected:
	TextGo text;
public:
	UiGameOver(const std::string& name = "");
	~UiGameOver() = default;

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

	void OnLocalize(Languages lang);
	
};
