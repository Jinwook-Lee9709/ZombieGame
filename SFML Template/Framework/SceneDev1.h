#pragma once
#include "Scene.h"
#include "json.hpp"

using json = nlohmann::json;

struct person {
	std::string name;
	std::vector<int> vec;
	int age;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(person, name, vec, age)
};


class SceneDev1 : public Scene
{
protected:
	sf::RectangleShape rect1;
	sf::RectangleShape rect2;
	sf::RectangleShape rect3;

public:
	SceneDev1();
	~SceneDev1() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

