#pragma once

class RenderEngine
{
public:
	virtual void InitTextures() = 0;
	virtual void InitTextures(std::string path_arg) = 0;
	virtual void InitSprite() = 0;
	virtual void Render(sf::RenderTarget& target) = 0;
	virtual void Render(sf::RenderTarget& target, DIR::Direction dir, DIR::Direction last) = 0;
	virtual void Update(DIR::Direction dir, DIR::Direction last) = 0;
};

