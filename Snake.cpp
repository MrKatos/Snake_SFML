#include "stdafx.h"
#include "Snake.h"

Snake::Snake(float x_arg, float y_arg, sf::Color color)
{
	this->x = x_arg;
	this->y = y_arg;
	this->circle.setOrigin(sf::Vector2f(this->size / 3, this->size / 3));
	this->circle.setPosition(sf::Vector2f(x_arg, y_arg));
	this->circle.setRadius(this->size/3);
	this->circle.setFillColor(color);
}

Snake::Snake(float x_arg, float y_arg, sf::Color color, bool face_arg)
{
	this->LEFT = sf::Vector2f(8.5f, 7.f);
	this->RIGHT = sf::Vector2f(-8.5f, 7.f);

	this->LEFT_UP = sf::Vector2f(7.f, -8.5f);
	this->RIGHT_UP = sf::Vector2f(7.f, 8.5f);

	this->face = face_arg;
	this->x = x_arg;
	this->y = y_arg;
	this->circle.setOrigin(sf::Vector2f(this->size / 3, this->size / 3));
	this->circle.setPosition(sf::Vector2f(x_arg, y_arg));
	this->circle.setRadius(this->size / 3);
	this->circle.setFillColor(color);
	this->InitTextures();
	this->InitSprite();
}

Snake::~Snake()
{
	std::cout << "Circle deleted" << std::endl;
}

void Snake::Move(sf::Vector2f vec)
{
	this->x += vec.x;
	this->y += vec.y;
	this->circle.setPosition(this->x, this->y);
}

sf::Vector2f Snake::GetSnakePosition()
{
	return sf::Vector2f(this->x, this->y);
}

void Snake::SetSnakePosition(sf::Vector2f vec)
{
	this->x = vec.x;
	this->y = vec.y;
	this->circle.setPosition(this->x, this->y);
}

void Snake::InitTextures()
{
	if (!this->texture_eye.loadFromFile("texture/eye.png"))
	{
		std::cout << "Texture couldn't be loaded" << std::endl;
	}
	else
	{
		this->texture_eye.setSmooth(true);
	}
	if (!this->texture_eye_ball.loadFromFile("texture/eye_ball.png"))
	{
		std::cout << "Texture couldn't be loaded" << std::endl;
	}
	else
	{
		this->texture_eye_ball.setSmooth(true);
	}
}

void Snake::InitSprite()
{
	this->eye.setTexture(this->texture_eye);
	this->eye.setOrigin(32.f, 32.f);
	this->eye.setScale(0.5f, 0.5f);
	this->eye.setPosition(this->circle.getPosition());

	this->eye_ballR.setTexture(this->texture_eye_ball);
	this->eye_ballR.setOrigin(32.f, 32.f);
	this->eye_ballR.setScale(0.25f, 0.25f);
	this->eye_ballR.setPosition(this->circle.getPosition() + RIGHT);

	this->eye_ballL.setTexture(this->texture_eye_ball);
	this->eye_ballL.setOrigin(32.f, 32.f);
	this->eye_ballL.setScale(0.25f, 0.25f);
	this->eye_ballL.setPosition(this->circle.getPosition() - LEFT);
}

void Snake::Render(sf::RenderTarget& target)
{
	target.draw(this->circle);
}

void Snake::Render(sf::RenderTarget& target, DIR::Direction dir, DIR::Direction last)
{
	this->Update(dir, last);
	target.draw(this->circle);
	target.draw(this->eye);
	target.draw(this->eye_ballR);
	target.draw(this->eye_ballL);
}

void Snake::Update(DIR::Direction dir, DIR::Direction last)
{
	switch (dir)
	{
	case DIR::LEFT:
		this->eye.setRotation(180);
		this->eye.setPosition(this->circle.getPosition());
		this->eye_ballR.setPosition(this->circle.getPosition() - RIGHT);
		this->eye_ballL.setPosition(this->circle.getPosition() + LEFT);
		this->eye_ballR.setRotation(this->Designate_APPLE_EYE_Angle(this->eye_ballR.getPosition().x, this->eye_ballR.getPosition().y));
		this->eye_ballL.setRotation(this->Designate_APPLE_EYE_Angle(this->eye_ballL.getPosition().x, this->eye_ballL.getPosition().y));
		break;
	case DIR::RIGHT:
		this->eye.setRotation(0);
		this->eye.setPosition(this->circle.getPosition());
		this->eye_ballR.setPosition(this->circle.getPosition() + RIGHT);
		this->eye_ballL.setPosition(this->circle.getPosition() - LEFT);
		this->eye_ballR.setRotation(this->Designate_APPLE_EYE_Angle(this->eye_ballR.getPosition().x, this->eye_ballR.getPosition().y));
		this->eye_ballL.setRotation(this->Designate_APPLE_EYE_Angle(this->eye_ballL.getPosition().x, this->eye_ballL.getPosition().y));
		break;
	case DIR::UP:
		this->eye.setRotation(270);
		this->eye.setPosition(this->circle.getPosition());
		this->eye_ballR.setPosition(this->circle.getPosition() - LEFT_UP);
		this->eye_ballL.setPosition(this->circle.getPosition() + RIGHT_UP);
		this->eye_ballR.setRotation(this->Designate_APPLE_EYE_Angle(this->eye_ballR.getPosition().x, this->eye_ballR.getPosition().y));
		this->eye_ballL.setRotation(this->Designate_APPLE_EYE_Angle(this->eye_ballL.getPosition().x, this->eye_ballL.getPosition().y));
		break;
	case DIR::DOWN:
		this->eye.setRotation(90);
		this->eye.setPosition(this->circle.getPosition());
		this->eye_ballR.setPosition(this->circle.getPosition() + LEFT_UP);
		this->eye_ballL.setPosition(this->circle.getPosition() - RIGHT_UP);
		this->eye_ballR.setRotation(this->Designate_APPLE_EYE_Angle(this->eye_ballR.getPosition().x, this->eye_ballR.getPosition().y));
		this->eye_ballL.setRotation(this->Designate_APPLE_EYE_Angle(this->eye_ballL.getPosition().x, this->eye_ballL.getPosition().y));
		break;
	case DIR::STOP:
		if (last == DIR::LEFT)
		{
			this->eye.setRotation(180);
			this->eye.setPosition(this->circle.getPosition());
			this->eye_ballR.setPosition(this->circle.getPosition() - RIGHT);
			this->eye_ballL.setPosition(this->circle.getPosition() + LEFT);
			this->eye_ballR.setRotation(this->Designate_APPLE_EYE_Angle(this->eye_ballR.getPosition().x, this->eye_ballR.getPosition().y));
			this->eye_ballL.setRotation(this->Designate_APPLE_EYE_Angle(this->eye_ballL.getPosition().x, this->eye_ballL.getPosition().y));
		}
		else if (last == DIR::RIGHT)
		{
			this->eye.setRotation(0);
			this->eye.setPosition(this->circle.getPosition());
			this->eye_ballR.setPosition(this->circle.getPosition() + RIGHT);
			this->eye_ballL.setPosition(this->circle.getPosition() - LEFT);
			this->eye_ballR.setRotation(this->Designate_APPLE_EYE_Angle(this->eye_ballR.getPosition().x, this->eye_ballR.getPosition().y));
			this->eye_ballL.setRotation(this->Designate_APPLE_EYE_Angle(this->eye_ballL.getPosition().x, this->eye_ballL.getPosition().y));
		}
		else if (last == DIR::UP)
		{
			this->eye.setRotation(270);
			this->eye.setPosition(this->circle.getPosition());
			this->eye_ballR.setPosition(this->circle.getPosition() - LEFT_UP);
			this->eye_ballL.setPosition(this->circle.getPosition() + RIGHT_UP);
			this->eye_ballR.setRotation(this->Designate_APPLE_EYE_Angle(this->eye_ballR.getPosition().x, this->eye_ballR.getPosition().y));
			this->eye_ballL.setRotation(this->Designate_APPLE_EYE_Angle(this->eye_ballL.getPosition().x, this->eye_ballL.getPosition().y));
		}
		else if (last == DIR::DOWN)
		{
			this->eye.setRotation(90);
			this->eye.setPosition(this->circle.getPosition());
			this->eye_ballR.setPosition(this->circle.getPosition() + LEFT_UP);
			this->eye_ballL.setPosition(this->circle.getPosition() - RIGHT_UP);
			this->eye_ballR.setRotation(this->Designate_APPLE_EYE_Angle(this->eye_ballR.getPosition().x, this->eye_ballR.getPosition().y));
			this->eye_ballL.setRotation(this->Designate_APPLE_EYE_Angle(this->eye_ballL.getPosition().x, this->eye_ballL.getPosition().y));
		}
		break;
	}
}

void Snake::Set_Eye_Rotation(int angle)
{
	this->eye.setRotation(angle);
}

void Snake::Update_Apple_Position(sf::Vector2f pos)
{
	this->APPLE_POS = pos;
}

float Snake::Designate_APPLE_EYE_Angle(float x_arg, float y_arg)
{
	if (this->APPLE_POS.x < x_arg && this->APPLE_POS.y > y_arg)
	{
		float x = std::abs(this->APPLE_POS.x - x_arg);
		float y = std::abs(this->APPLE_POS.y - y_arg);
		return (std::atan(y / x) * 180.0f / 3.14f) + 90;
	}
	else if(this->APPLE_POS.x < x_arg && this->APPLE_POS.y < y_arg)
	{
		float x = std::abs(this->APPLE_POS.x - x_arg);
		float y = std::abs(this->APPLE_POS.y - y_arg);
		return (std::atan(y / x) * 180.0f / 3.14f) + 180;
	}
	else if (this->APPLE_POS.x > x_arg && this->APPLE_POS.y < y_arg)
	{
		float x = std::abs(this->APPLE_POS.x - x_arg);
		float y = std::abs(this->APPLE_POS.y - y_arg);
		return (std::atan(y / x) * 180.0f / 3.14f) + 270.f;
	}
	else if (this->APPLE_POS.x > x_arg && this->APPLE_POS.y > y_arg)
	{
		float x = std::abs(this->APPLE_POS.x - x_arg);
		float y = std::abs(this->APPLE_POS.y - y_arg);
		return (std::atan(y / x) * 180.0f / 3.14f);
	}
}

void Snake::SetDeadReason(DEAD::Dead_Reason reason_arg)
{
	this->reason = reason_arg;
}

const DEAD::Dead_Reason Snake::GetDeadReason() const
{
	return this->reason;
}
