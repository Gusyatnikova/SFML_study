#pragma once
#include "Window.h"
#include "World.h"
#include"textbox.h"


class Game
{
public:
	Game();
	~Game();

	void HandleInput();
	void Update();
	void Render();
	void ShowGameOver();
	Window* GetWindow();
	sf::Time GetElapsed();
	void RestartClock();
	bool IsDone() const;
private:
	Window m_window;
	World m_world;
	Snake m_snake;
	sf::Clock m_clock;
	float m_elapsed;
	TextBox m_textBox;
	bool m_isDone;
};

