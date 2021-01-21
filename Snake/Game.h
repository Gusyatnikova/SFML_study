#pragma once
#include "Window.h"
#include "World.h"
#include"textbox.h"
#include "state_manager.h"

class Game
{
public:
	Game();
	~Game();

	//void HandleInput();
	void Update();
	void LateUpdate();
	void Render();
	//void ShowGameOver();
	Window* GetWindow();
	sf::Time GetElapsed();
	void RestartClock();
	bool IsDone() const;
private:
	Window m_window;
	SharedContext m_context;
	StateManager m_stateManager;
	World m_world;
	Snake m_snake;
	sf::Clock m_clock;
	sf::Time m_elapsed;
	TextBox m_textBox;
	bool m_isDone;
};

