#pragma once

class Apple : public sf::Sprite
{
private:
	sf::Texture texture;
	const float scale = 0.08f;
public:
	Apple();
	void Generate_Position();
};

