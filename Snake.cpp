#include "stdafx.h"
#include "Snake.h"

Snake::Snake(float x_arg, float y_arg, sf::Color color)
{
	this->x = x_arg;
	this->y = y_arg;
	this->setOrigin(sf::Vector2f(this->size/3, this->size/3));
	this->setPosition(sf::Vector2f(x_arg, y_arg));
	this->setRadius(this->size/3);
	this->setFillColor(color);
}

void Snake::Move(sf::Vector2f vec)
{
	this->x += vec.x;
	this->y += vec.y;
	this->setPosition(this->x, this->y);
}

sf::Vector2f Snake::GetSnakePosition()
{
	return sf::Vector2f(this->x, this->y);
}
