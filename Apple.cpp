#include "stdafx.h"
#include "Apple.h"

Apple::Apple()
{
	this->texture.loadFromFile("texture/apple.png");
	this->texture.setSmooth(true);

	this->setTexture(this->texture);
	this->setOrigin(225.f, 225.f);
	this->setScale(this->scale, this->scale);
	this->Generate_Position();
}

void Apple::Generate_Position()
{
	float x = std::rand() % 16;
	float y = std::rand() % 16;
	this->setPosition(32.f * x + 42.7f, 32.f * y + 101.7f);
}

