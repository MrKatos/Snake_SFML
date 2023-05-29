#include "stdafx.h"
#include "Texture_Manager.h"

Texture_Manager::Texture_Manager()
{
}

Texture_Manager::Texture_Manager(float x_pos, float y_pos, float scale, float size_x, float size_y, std::string file_path)
{
	this->texture.loadFromFile(file_path);
	this->texture.setSmooth(true);

	this->setTexture(this->texture);
	this->setOrigin(size_x, size_y);
	this->setScale(scale, scale);
	this->setPosition(x_pos, y_pos);
}

Texture_Manager::Texture_Manager(float x_pos, float y_pos, float scale, float size_x, float size_y, std::string file_path, sf::Color color)
{
	this->texture.loadFromFile(file_path);
	this->texture.setSmooth(true);

	this->setTexture(this->texture);
	this->setOrigin(size_x, size_y);
	this->setScale(scale, scale);
	this->setPosition(x_pos, y_pos);
	this->setColor(color);
}

Texture_Manager::~Texture_Manager()
{
	std::cout << "Usunieto texture" << std::endl;
}