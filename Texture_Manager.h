#pragma once
#include "RenderEngine.h"

class Texture_Manager : public RenderEngine
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
public:
	Texture_Manager() { std::cout << "Texture created" << std::endl; };
	Texture_Manager(float x_pos, float y_pos, float scale, float size_x, float size_y, std::string file_path);
	Texture_Manager(float x_pos, float y_pos, float scale, float size_x, float size_y, std::string file_path, sf::Color color);
	~Texture_Manager();

	void InitTextures() {};
	void InitTextures(std::string path_arg) override;
	void InitSprite() {};
	void Render(sf::RenderTarget& target) override;
	void Render(sf::RenderTarget& target, DIR::Direction dir, DIR::Direction last) {};
	void Update(DIR::Direction dir, DIR::Direction last) {};
	sf::FloatRect GetGlobalBounds();
	void SetColor(sf::Color color);
};

