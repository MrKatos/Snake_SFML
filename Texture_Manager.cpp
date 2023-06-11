#include "stdafx.h"
#include "Texture_Manager.h"

Texture_Manager::Texture_Manager(float x_pos, float y_pos, float scale, float size_x, float size_y, std::string file_path)
{
	this->InitTextures(file_path);
	this->sprite.setTexture(this->texture);
	this->sprite.setOrigin(size_x, size_y);
	this->sprite.setScale(scale, scale);
	this->sprite.setPosition(x_pos, y_pos);
	std::cout << "Texture created" << std::endl;
}

Texture_Manager::Texture_Manager(float x_pos, float y_pos, float scale, float size_x, float size_y, std::string file_path, sf::Color color)
{
	this->InitTextures(file_path);
	this->sprite.setTexture(this->texture);
	this->sprite.setOrigin(size_x, size_y);
	this->sprite.setScale(scale, scale);
	this->sprite.setPosition(x_pos, y_pos);
	this->sprite.setColor(color);
	std::cout << "Texture created" << std::endl;
}

Texture_Manager::~Texture_Manager()
{
	std::cout << "Texture deleted" << std::endl;
}

void Texture_Manager::InitTextures(std::string path_arg)
{
	if (!this->texture.loadFromFile(path_arg))
	{
		std::cout << "Texture from path: " << path_arg << " couldn't be loaded" << std::endl;
	}
	else
	{
		this->texture.setSmooth(true);
	}
}

void Texture_Manager::Render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

sf::FloatRect Texture_Manager::GetGlobalBounds()
{
	return this->sprite.getGlobalBounds();
}

void Texture_Manager::SetColor(sf::Color color)
{
	this->sprite.setColor(color);
}
