#pragma once

class Snake : public sf::CircleShape
{
private:
	sf::Color color;

	float x = 0;
	float y = 0;

	const float size = 32;

public:
	Snake(float x_arg, float y_arg, sf::Color color);
	void Move(sf::Vector2f vec);
	sf::Vector2f GetSnakePosition();
	void SetSnakePosition(sf::Vector2f vec)
	{
		this->x = vec.x;
		this->y = vec.y;
		this->setPosition(this->x, this->y);
	}
};

