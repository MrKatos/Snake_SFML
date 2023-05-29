#pragma once

class Texture_Manager : public sf::Sprite
{
private:
	sf::Texture texture;
public:
	Texture_Manager();
	Texture_Manager(float x_pos, float y_pos, float scale, float size_x, float size_y, std::string file_path);
	Texture_Manager(float x_pos, float y_pos, float scale, float size_x, float size_y, std::string file_path, sf::Color color);
	~Texture_Manager();
};

