#include "stdafx.h"
#include "SceneDev1.h"

SceneDev1::SceneDev1() : Scene(SceneIds::Dev1)
{
}

void SceneDev1::Init()
{
	auto text = AddGo(new TextGo("fonts/DS-DIGI.ttf", "Scene Name"));
	
	Scene::Init();

	text->sortingLayer = SortingLayers::UI;
	text->Set(25, sf::Color::White);
	text->SetString("Dev 1");
}

void SceneDev1::Enter()
{
	rect1.setSize({ 200.f, 100.f });
	rect1.setFillColor(sf::Color::Blue);
	Utils::SetOrigin(rect1, Origins::MC);

	rect2.setSize({ 100.f, 200.f });
	rect2.setFillColor(sf::Color::Green);
	Utils::SetOrigin(rect1, Origins::MC);

	rect3.setSize({ 10.f, 10.f });
	rect3.setFillColor(sf::Color::White);
	Utils::SetOrigin(rect1, Origins::MC);

	Scene::Enter();

	worldView.setCenter({ 0.f, 0.f });
	worldView.setSize(FRAMEWORK.GetWindowSizeF());

}

void SceneDev1::Exit()
{
	Scene::Exit();
}

void SceneDev1::Update(float dt)
{ 
	Scene::Update(dt);

	rect1.rotate(100.f * dt);
	rect3.setPosition(ScreenToWorld(InputMgr::GetMousePosition()));
	rect3.setFillColor(sf::Color::Magenta);
	if (InputMgr::GetMouseButton(sf::Mouse::Left)) 
	{
		sf::Vector2f mousePos = ScreenToWorld(InputMgr::GetMousePosition());
		rect2.setPosition(mousePos);
	}

	if (Utils::CheckCollision(rect1, rect2))
	{
		rect2.setFillColor(sf::Color::Red);
	}
	else {
		rect2.setFillColor(sf::Color::Green);
	}
	if (Utils::PointInTransformBounds(rect1,rect1.getLocalBounds(), ScreenToWorld(InputMgr::GetMousePosition())))
	{
		rect1.setFillColor(sf::Color::Magenta);
	}
	else {
		rect1.setFillColor(sf::Color::Blue);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SCENE_MGR.ChangeScene(SceneIds::Dev2);
	}
}

void SceneDev1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.draw(rect1);
	window.draw(rect2);
	window.draw(rect3);
}
