#pragma once
#include "RenderEngine.h"

class Snake : public RenderEngine
{
private:
	sf::Texture texture_eye;
	sf::Texture texture_eye_ball;
	sf::Sprite eye;
	sf::Sprite eye_ballR;
	sf::Sprite eye_ballL;

	sf::Vector2f LEFT;
	sf::Vector2f RIGHT;

	sf::Vector2f LEFT_UP;
	sf::Vector2f RIGHT_UP;

	sf::Vector2f APPLE_POS;

	sf::Color color;
	sf::CircleShape circle;
	DEAD::Dead_Reason reason = DEAD::UNKNOWN;

	float x = 0;
	float y = 0;

	const float size = 32;

	bool face = false;
public:
	Snake(float x_arg, float y_arg, sf::Color color);
	Snake(float x_arg, float y_arg, sf::Color color, bool face_arg);
	~Snake();

	void Move(sf::Vector2f vec);
	sf::Vector2f GetSnakePosition();
	void SetSnakePosition(sf::Vector2f vec);
	void InitTextures() override;
	void InitSprite() override;
	void Render(sf::RenderTarget& target) override;
	void Render(sf::RenderTarget& target, DIR::Direction dir, DIR::Direction last) override;
	void Update(DIR::Direction dir, DIR::Direction last) override;
	void InitTextures(std::string path_arg) {};
	void Set_Eye_Rotation(int angle);
	void Update_Apple_Position(sf::Vector2f pos);
	float Designate_APPLE_EYE_Angle(float x_arg, float y_arg);

	void SetDeadReason(DEAD::Dead_Reason reason_arg);
	const DEAD::Dead_Reason GetDeadReason() const;

	friend std::ostream& operator<<(std::ostream& os, const Snake& snake)
	{
		switch (snake.GetDeadReason())
		{
		case DEAD::TAIL:
			return os << "Snake killed by his tail";
			break;
		case DEAD::WALL:
			return os << "Snake killed by wall";
			break;
		case DEAD::UNKNOWN:
			return os << "Unkown reason of death";
			break;
		}
	}
};

