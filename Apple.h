#pragma once
#include "RenderEngine.h"

class Apple : public RenderEngine
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	const float scale = 0.08f;

public:
	Apple();
	void Generate_Position();

	void InitTextures() override;
	void InitSprite() override;
	void Render(sf::RenderTarget& target) override;
	void Render(sf::RenderTarget& target, DIR::Direction dir, DIR::Direction last) {};
	void Update(DIR::Direction dir, DIR::Direction last) {};
	void InitTextures(std::string path_arg) {};
	const sf::Vector2f GetPosition() const;

	friend std::ostream& operator<<(std::ostream& os, const Apple& apple)
	{
		return os << "[" << (apple.GetPosition().x - 42.7f) / 32.f << ", " << (apple.GetPosition().y - 101.7f) / 32.f << "]";
	}
};

