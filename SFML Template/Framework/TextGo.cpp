#include "stdafx.h"
#include "TextGo.h"

TextGo::TextGo()
{
}

TextGo::TextGo(const std::string& fontId, const std::string& name)
	: GameObject(name), fontId(fontId)
{
}


void TextGo::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = Utils::SetOrigin(text, originPreset);
}

void TextGo::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	text.setOrigin(origin);
}

void TextGo::Reset()
{
	text.setFont(FONT_MGR.Get(fontId));
	SetString(stringId);
}

void TextGo::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	text.setPosition(pos);
}

void TextGo::SetRotation(float angle)
{
	rotation = angle;
	text.setRotation(angle);
}

void TextGo::SetScale(const sf::Vector2f& s)
{
	scale = s;
	text.setScale(scale);
}

void TextGo::SetCharacterSize(float size)
{
	text.setCharacterSize(size);
	SetOrigin(origin);
}

void TextGo::SetFillColor(const sf::Color& color)
{
	text.setFillColor(color);
}

void TextGo::Draw(sf::RenderWindow& window)
{
	window.draw(text);
}

void TextGo::OnLocalize(Languages lang)
{
	text.setString(STRING_TABLE->Get(stringId, lang));
	SetOrigin(originPreset);
}

void TextGo::Set(int size, const sf::Color &color)
{
	text.setCharacterSize(size);
	text.setFillColor(color);
}

void TextGo::SetString(const std::string& id)
{
	stringId = id;
	text.setString(STRING_TABLE->Get(stringId));
	SetOrigin(originPreset);
}
void TextGo::SetString(const std::wstring& str)
{
	text.setString(str);
	SetOrigin(originPreset);
}

void TextGo::SetFont(const std::string& font)
{
	fontId = font;
	text.setFont(FONT_MGR.Get(fontId));
}

sf::FloatRect TextGo::GetLocalBounds()
{
	return text.getLocalBounds();
}

sf::FloatRect TextGo::GetGlobalBounds()
{
	return text.getGlobalBounds();
}





void TextGo::Init()
{
}

void TextGo::Release()
{
}

void TextGo::Update(float dt)
{
}
