#include "stdafx.h"
#include "Game_Engine.h"

Game_Engine::Game_Engine()
{
	this->Init_Window();
	this->Init_Best_Score();
	this->Init_Text();
	this->Set_Constant_Textures();
	this->Set_Menu_Textures();
	this->Create_Snake();
	this->Create_Apple();
	this->Is_Snake_On_The_Spot();
}

void Game_Engine::Run()
{
	while (this->window.isOpen())
	{
		this->elapsed += this->clock.restart();
		this->time_per_frame = sf::seconds(1.f / this->speed);

		// CONTROLS
		this->Pull_Events();

		// SNAKE MOVEMENT
		if (this->elapsed >= this->time_per_frame)
		{
			this->Smooth_Snake_Motion();
			this->elapsed -= this->time_per_frame;
		}

		// MENU ODRADZANIA
		if (this->Is_Snake_Dead)
		{
			this->Init_Replay_Menu();
			this->Is_Snake_Dead = false;
			this->In_Menu = true;
			this->Reset_Game();
		}
		// WINDOW UPDATE
		this->window.clear(sf::Color::Transparent);
		this->Draw_Objects();
		this->window.display();
	}
}

//INITIALIZATION
void Game_Engine::Init_Text()
{
	//this->score_text = new Text_Elements(50.f, 60.f, std::to_string(this->score));
	if (!this->font.loadFromFile("font/OpenSans-Medium.ttf"))
	{
		std::cout << "Nie udalo sie zaladowac czcionki" << std::endl;
	}

	this->score_text.setFont(this->font);
	this->score_text.setString(std::to_string(this->score));
	this->score_text.setCharacterSize(46);
	this->score_text.setFillColor(sf::Color::White);
	this->score_text.setStyle(sf::Text::Regular);
	this->score_text.setPosition(100.f, 7.f);

	this->best_score_text.setFont(this->font);
	this->best_score_text.setString(this->best_score);
	this->best_score_text.setCharacterSize(46);
	this->best_score_text.setFillColor(sf::Color::White);
	this->best_score_text.setStyle(sf::Text::Regular);
	this->best_score_text.setPosition(240.f, 7.f);
}

void Game_Engine::Init_Replay_Menu()
{
	this->free_elements.push_back(new Texture_Manager(282.5, 312.5, 0.5f, 200.f, 64.f, "texture/replay_button.png", sf::Color(230, 230, 230, 255)));
}

void Game_Engine::Init_Window() // Wymiary okna : 565 x 625
{
	this->settings.antialiasingLevel = 8;
	this->window.create(sf::VideoMode(565, 625), "Snake", sf::Style::None, settings);
	this->window.setFramerateLimit(60);
	this->margins.cxLeftWidth = -1;
	SetWindowLong(this->window.getSystemHandle(), GWL_STYLE, WS_POPUP | WS_VISIBLE);
	DwmExtendFrameIntoClientArea(this->window.getSystemHandle(), &this->margins);
	sf::Image icon;
	icon.loadFromFile("texture/snake.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void Game_Engine::Set_Best_Score()
{
	if (std::stoi(this->best_score) <= this->score)
	{
		std::ofstream out("data/best_score.txt", std::ios::trunc);
		out << std::to_string(this->score);
		out.close();
	}
	this->Init_Best_Score();
}

void Game_Engine::Init_Best_Score()
{
	std::ifstream input("data/best_score.txt");
	std::getline(input, this->best_score);
	input.close();
}

//TEXTURES
void Game_Engine::Set_Constant_Textures()
{
	this->back_groud.push_back(new Texture_Manager(282.5f, 312.5f, 0.7882f, 400.f, 400.f, "texture/Tlo_Snake2.png", sf::Color(190, 190, 190, 255)));
	this->back_groud.push_back(new Texture_Manager(530.f, 35.f, 0.5f, 50.f, 50.f, "texture/close_button.png", sf::Color(190, 190, 190, 255)));
}

void Game_Engine::Set_Menu_Textures()
{
	this->free_elements.push_back(new Texture_Manager(282.5, 312.5, 0.5f, 200.f, 64.f, "texture/play_button.png", sf::Color(230, 230, 230, 255)));
	this->pause_button = new Texture_Manager(282.5, 312.5, 0.7f, 256.f, 256.f, "texture/pause.png", sf::Color(255, 255, 255, 255));
	this->winner = new Texture_Manager(282.5, 172.5, 0.4f, 256.f, 256.f, "texture/winner.png", sf::Color(255, 255, 255, 255));
}

void Game_Engine::Delete_Textures()
{
	for (size_t i = 0; i < free_elements.size(); i++)
	{
		delete this->free_elements[i];
	}
}

void Game_Engine::Draw_Objects()
{
	for (size_t i = 0; i < back_groud.size(); i++)
	{
		this->back_groud[i]->Render(this->window);
	}
	this->window.draw(score_text);
	this->window.draw(best_score_text);
	this->apple->Render(this->window);
	for (size_t i = 1; i < this->snake.size(); i++)
	{
		this->snake[i]->Render(this->window);
	}
	this->snake[0]->Render(this->window, this->snake_direction, this->last_snake_direction);
	for (size_t i = 0; i < this->free_elements.size(); i++)
	{
		this->free_elements[i]->Render(this->window);
	}
	if (this->Pause)
	{
		this->pause_button->Render(this->window);
	}
	if (this->WON)
	{
		this->winner->Render(this->window);
	}
}

//SNAKE
void Game_Engine::Create_Snake() // pozycja zerowa x = 298.5, y = 325.5 (42.7, 101.7)
{
	this->snake.push_back(new Snake(298.7f, 325.7f, sf::Color(84, 118, 229), true));
	this->snake.push_back(new Snake(294.7f, 325.7f, sf::Color(84, 118, 229)));
	this->snake.push_back(new Snake(290.7f, 325.7f, sf::Color(84, 118, 229)));
	this->snake.push_back(new Snake(286.7f, 325.7f, sf::Color(84, 118, 229)));
}
	
	//MOVEMENT
void Game_Engine::Smooth_Snake_Motion()
{
	if (this->score >= 256)
	{
		this->snake_direction = DIR::STOP;
		this->last_snake_direction = DIR::STOP;
		this->Is_Snake_Dead = true;
		this->WON = true;
	}
	if (this->Is_Snake_Outside())
	{
		this->snake_direction = DIR::STOP;
		this->last_snake_direction = DIR::STOP;
		this->Is_Snake_Dead = true;
	}
	if (this->score > 4)
	{
		this->Touch_His_Body();
	}
	if (this->Is_Snake_On_The_Spot())
	{
		switch (this->snake_direction)
		{
		case DIR::LEFT:
			this->last_position = this->snake[0]->GetSnakePosition();
			this->snake[0]->Move(sf::Vector2f(-this->snake_speed, 0.f));
			for (size_t i = 1; i < this->snake.size(); ++i)
			{
				this->last_position_2 = this->snake[i]->GetSnakePosition();
				this->snake[i]->SetSnakePosition(this->last_position);
				this->last_position = this->last_position_2;
			}
			this->last_snake_direction = DIR::LEFT;
			break;

		case DIR::RIGHT:
			this->last_position = this->snake[0]->GetSnakePosition();
			this->snake[0]->Move(sf::Vector2f(this->snake_speed, 0.f));
			for (size_t i = 1; i < this->snake.size(); ++i)
			{
				this->last_position_2 = this->snake[i]->GetSnakePosition();
				this->snake[i]->SetSnakePosition(this->last_position);
				this->last_position = this->last_position_2;
			}
			this->last_snake_direction = DIR::RIGHT;
			break;

		case DIR::UP:
			this->last_position = this->snake[0]->GetSnakePosition();
			this->snake[0]->Move(sf::Vector2f(0.f, -this->snake_speed));
			for (size_t i = 1; i < this->snake.size(); ++i)
			{
				this->last_position_2 = this->snake[i]->GetSnakePosition();
				this->snake[i]->SetSnakePosition(this->last_position);
				this->last_position = this->last_position_2;
			}
			this->last_snake_direction = DIR::UP;
			break;

		case DIR::DOWN:
			this->last_position = this->snake[0]->GetSnakePosition();
			this->snake[0]->Move(sf::Vector2f(0.f, this->snake_speed));
			for (size_t i = 1; i < this->snake.size(); ++i)
			{
				this->last_position_2 = this->snake[i]->GetSnakePosition();
				this->snake[i]->SetSnakePosition(this->last_position);
				this->last_position = this->last_position_2;
			}
			this->last_snake_direction = DIR::DOWN;
			break;

		case DIR::STOP:
			break;
		}
	}
	else
	{
		switch (this->last_snake_direction)
		{
		case DIR::LEFT:
			this->last_position = this->snake[0]->GetSnakePosition();
			this->snake[0]->Move(sf::Vector2f(-this->snake_speed, 0.f));
			for (size_t i = 1; i < this->snake.size(); ++i)
			{
				this->last_position_2 = this->snake[i]->GetSnakePosition();
				this->snake[i]->SetSnakePosition(this->last_position);
				this->last_position = this->last_position_2;
			}
			break;

		case DIR::RIGHT:
			this->last_position = this->snake[0]->GetSnakePosition();
			this->snake[0]->Move(sf::Vector2f(this->snake_speed, 0.f));
			for (size_t i = 1; i < this->snake.size(); ++i)
			{
				this->last_position_2 = this->snake[i]->GetSnakePosition();
				this->snake[i]->SetSnakePosition(this->last_position);
				this->last_position = this->last_position_2;
			}
			break;

		case DIR::UP:
			this->last_position = this->snake[0]->GetSnakePosition();
			this->snake[0]->Move(sf::Vector2f(0.f, -this->snake_speed));
			for (size_t i = 1; i < this->snake.size(); ++i)
			{
				this->last_position_2 = this->snake[i]->GetSnakePosition();
				this->snake[i]->SetSnakePosition(this->last_position);
				this->last_position = this->last_position_2;
			}
			break;

		case DIR::DOWN:
			this->last_position = this->snake[0]->GetSnakePosition();
			this->snake[0]->Move(sf::Vector2f(0.f, this->snake_speed));
			for (size_t i = 1; i < this->snake.size(); ++i)
			{
				this->last_position_2 = this->snake[i]->GetSnakePosition();
				this->snake[i]->SetSnakePosition(this->last_position);
				this->last_position = this->last_position_2;
			}
			break;

		case DIR::STOP:
			break;
		}
	}
	this->Apple_Eaten();
}
	
	//QUESTIONS
bool Game_Engine::Is_Snake_On_The_Spot()
{
	for (int i = 0; i < 16; ++i)
	{
		if (static_cast<int>(this->snake[0]->GetSnakePosition().x) == i * 32 + 42)
		{
			for (int j = 0; j < 16; ++j)
			{
				if (static_cast<int>(this->snake[0]->GetSnakePosition().y) == j * 32 + 101)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool Game_Engine::Is_Snake_Outside()
{
	if(this->snake[0]->GetSnakePosition().x > 522.7f || this->snake[0]->GetSnakePosition().x < 42.7f || this->snake[0]->GetSnakePosition().y > 581.7f || this->snake[0]->GetSnakePosition().y < 101.7f)
	{
		this->snake[0]->SetDeadReason(DEAD::WALL);
		std::cout << *this->snake[0] << std::endl;
		this->Set_Best_Score();
		return true;
	}
	return false;
}

	//FUNCTIONS
void Game_Engine::Touch_His_Body()
{
	for (size_t i = 16; i < this->snake.size(); ++i)
	{
		sf::Vector2f diff = this->snake[0]->GetSnakePosition() - this->snake[i]->GetSnakePosition();
		float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);
		if (distance <= 21.37f)
		{
			this->snake[0]->SetDeadReason(DEAD::TAIL);
			this->snake_direction = DIR::STOP;
			this->last_snake_direction = DIR::STOP;
			this->Set_Best_Score();
			std::cout << *this->snake[0] << std::endl;
			this->Is_Snake_Dead = true;
		}
	}
}

void Game_Engine::Reset_Game()
{
	this->Kill_Snake();
	this->Reset_Score();
}

void Game_Engine::Reset_Score()
{
	this->score = 0;
}

void Game_Engine::Occupied_Spot()
{
	//for (size_t i = 0; i < length; ++i)
	//{
	//	for (size_t j = 0; j < length; j++)
	//	{
	//
	//	}
	//}
}

void Game_Engine::Increase_Snake_Length()
{
	this->snake.push_back(new Snake(this->last_position_2.x, last_position_2.y, sf::Color(84, 118, 229)));
	this->snake.push_back(new Snake(this->last_position_2.x, last_position_2.y, sf::Color(84, 118, 229)));
	this->snake.push_back(new Snake(this->last_position_2.x, last_position_2.y, sf::Color(84, 118, 229)));
	this->snake.push_back(new Snake(this->last_position_2.x, last_position_2.y, sf::Color(84, 118, 229)));
	this->snake.push_back(new Snake(this->last_position_2.x, last_position_2.y, sf::Color(84, 118, 229)));
	this->snake.push_back(new Snake(this->last_position_2.x, last_position_2.y, sf::Color(84, 118, 229)));
	this->snake.push_back(new Snake(this->last_position_2.x, last_position_2.y, sf::Color(84, 118, 229)));
	this->snake.push_back(new Snake(this->last_position_2.x, last_position_2.y, sf::Color(84, 118, 229)));
}

void Game_Engine::Kill_Snake()
{
	for (size_t i = 0; i < this->snake.size(); ++i)
	{
		delete this->snake[i];
	}
	this->snake.clear();
	this->Create_Snake();
}

//APPLE
void Game_Engine::Apple_Eaten()
{
	sf::Vector2f diff = this->apple->GetPosition() - this->snake[0]->GetSnakePosition();
	float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);
	if (distance <= 25.f)
	{
		std::cout << "Deleted apple on position :" << *this->apple << std::endl;
		this->apple->Generate_Position();
		this->snake[0]->Update_Apple_Position(this->apple->GetPosition());
		std::cout << "Created apple on position :" << *this->apple << std::endl;
		this->Increase_Snake_Length();
		this->score += 1.f;
		this->score_text.setString(std::to_string(this->score));
	}
}

void Game_Engine::Create_Apple()
{
	this->apple = new Apple();
	this->snake[0]->Update_Apple_Position(this->apple->GetPosition());
}

//KEYBOARD
void Game_Engine::Check_Keyboard()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		this->window.close();
	}
	if (this->last_snake_direction != DIR::RIGHT)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			this->snake_direction = DIR::LEFT;
			this->Pause = false;
		}
	}
	if (this->last_snake_direction != DIR::LEFT)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			this->snake_direction = DIR::RIGHT;
			this->Pause = false;
		}
	}
	if (this->last_snake_direction != DIR::UP)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			this->snake_direction = DIR::DOWN;
			this->Pause = false;
		}
	}
	if (this->last_snake_direction != DIR::DOWN)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			this->snake_direction = DIR::UP;
			this->Pause = false;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		this->Pause = true;
		this->snake_direction = DIR::STOP;
	}
}

void Game_Engine::Pull_Events()
{
	sf::Event event;
	while (this->window.pollEvent(event))
	{
		if (!this->In_Menu)
		{
			this->Check_Keyboard();
		}
		// wykrywanie myszy oraz wcisniecia przycisku
		if (this->back_groud[1]->GetGlobalBounds().contains(this->window.mapPixelToCoords(sf::Mouse::getPosition(this->window))) && event.type == sf::Event::MouseButtonPressed)
		{
			this->window.close();
		}
		if (this->In_Menu)
		{
			if (this->free_elements[0]->GetGlobalBounds().contains(this->window.mapPixelToCoords(sf::Mouse::getPosition(this->window))) && event.type == sf::Event::MouseButtonPressed)
			{
				this->WON = false;
				this->In_Menu = false;
				this->back_groud[0]->SetColor(sf::Color(255, 255, 255, 255));
				delete this->free_elements[0];
				this->free_elements.clear();
			}
		}
		// wykrywanie myszy
		if (this->back_groud[1]->GetGlobalBounds().contains(this->window.mapPixelToCoords(sf::Mouse::getPosition(this->window))))
		{
			this->back_groud[1]->SetColor(sf::Color(255, 255, 255, 255));
		}
		else
		{
			this->back_groud[1]->SetColor(sf::Color(190, 190, 190, 255));
		}
		if (this->In_Menu)
		{
			if (this->free_elements[0]->GetGlobalBounds().contains(this->window.mapPixelToCoords(sf::Mouse::getPosition(this->window))))
			{
				this->free_elements[0]->SetColor(sf::Color(255, 255, 255, 255));
			}
			else
			{
				this->free_elements[0]->SetColor(sf::Color(190, 190, 190, 255));
			}
		}
	}
}


