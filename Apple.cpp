#include "stdafx.h"
#include "Apple.h"

Apple::Apple()
{
	this->InitTextures();
	this->InitSprite();
	this->Generate_Position();
	std::cout << "Apple created" << std::endl;
}

void Apple::InitTextures()
{
	if (!this->texture.loadFromFile("texture/apple.png"))
	{
		std::cout << "Couldn't load texture" << "\n";
	}
	else
	{
		this->texture.setSmooth(true);
	}
}

void Apple::InitSprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.setOrigin(225.f, 225.f);
	this->sprite.setScale(this->scale, this->scale);
}

void Apple::Render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

const sf::Vector2f Apple::GetPosition() const
{
	return this->sprite.getPosition();
}

void Apple::Generate_Position()
{
	float x = std::rand() % 16;
	float y = std::rand() % 16;
	this->sprite.setPosition(32.f * x + 42.7f, 32.f * y + 101.7f);
}



