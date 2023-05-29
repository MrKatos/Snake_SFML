#pragma once
#include "Texture_Manager.h"
#include "Snake.h"
#include "Apple.h"

class Game_Engine
{
private:
	//Elements to create window
	sf::ContextSettings settings;
	sf::RenderWindow window;
	MARGINS margins;

	//Class objects
	Texture_Manager obj;
	std::vector<Texture_Manager*> back_groud;
	std::vector<Texture_Manager*> free_elements;

	//SNAKE
	std::vector<Snake*> snake;
	DIR::Direction snake_direction = DIR::STOP;
	DIR::Direction last_snake_direction = DIR::RIGHT;
	sf::Vector2f last_position;
	sf::Vector2f last_position_2;
	float speed = 60;
	const float snake_speed = 4;

	//APPLE
	Apple* apple;

	//COLISIONS
	std::vector<std::vector<int>> matrix;

	//TIME
	sf::Clock clock;
	sf::Time elapsed;
	sf::Time time_per_frame;
	bool In_Menu = true;

	//SCORE
	sf::Text score_text, best_score_text;
	sf::Font font;
	int score = 0;
	std::string best_score;

public:
	Game_Engine();
	void Run();
	void Init_Window();
	void Init_Text();
	void Set_Constant_Textures();
	void Set_Menu_Textures();
	void Init_Best_Score();
	void Set_Best_Score();
	void Delete_Textures();
	void Draw_Objects();
	void Create_Snake();
	void Smooth_Snake_Motion();
	bool Is_Snake_On_The_Spot();
	bool Is_Snake_Outside();
	void Apple_Eaten();
	void Increase_Snake_Length();
	void Kill_Snake();
	void Check_Keyboard();
	void Create_Apple();
	void Occupied_Spot();
	void Touch_His_Body();
};

