#include "stdafx.h"
#include "SceneDev2.h"
#include "AniPlayer.h"
#include "AniPlayer2.h"

SceneDev2::SceneDev2() : Scene(SceneIds::Dev2)
{

}

void SceneDev2::Init()
{	
	AddGo(new AniPlayer2("Player"));
	/*AddGo(new AniPlayer("ANI TEST"));*/
	Scene::Init();
	/*auto text1 = AddGo(new TextGo("fonts/BMJUA.ttf", "Scene Name1"));
	auto text2 = AddGo(new TextGo("fonts/BMJUA.ttf", "Scene Name2"));
	Scene::Init();

	auto st = new StringTable();
	st -> Load();


	text1->sortingLayer = SortingLayers::UI;
	text1->Set(50, sf::Color::White);
	text1->SetString("Hi");
	text1->SetPosition({ 360, 300 });

	text2->sortingLayer = SortingLayers::UI;
	text2->Set(50, sf::Color::White);
	text2->SetString("Hi");
	text2->SetPosition({ 360, 500 });*/
}

void SceneDev2::Enter()
{
	Scene::Enter();
	worldView.setCenter(0.f, 0.f);
	worldView.setSize(FRAMEWORK.GetWindowSizeF());
}

void SceneDev2::Exit()
{
	Scene::Exit();
}

void SceneDev2::Update(float dt)
{
	Scene::Update(dt);

	/*if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SCENE_MGR.ChangeScene(SceneIds::Dev1);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		Variables::currentLang = Languages::Korean;
		OnLocalize(Variables::currentLang);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		Variables::currentLang = Languages::English;
		OnLocalize(Variables::currentLang);
	}*/
}

void SceneDev2::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
