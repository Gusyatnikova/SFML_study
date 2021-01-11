#pragma once

#include <string>

#include <SFML/Graphics.hpp>
#include "event_manager.h"

class Window
{
public:
	Window();
	Window(const std::string& l_title, const sf::Vector2u& l_size);
	~Window();

	void BeginDraw();
	void EndDraw();

	void Update();
	//void Close();

	bool IsDone() const;
	bool IsFullScreen() const;
	sf::Vector2u GetWindowSize() const;
	sf::RenderWindow* GetRenderWindow();

	bool IsFocused() const;
	EventManager* GetEventManager();
	void ToggleFullScreen(EventDetails *details);
	void Close(EventDetails *details = nullptr);

	void Draw(sf::Drawable& l_drawable);

private:
	void Setup(const std::string& l_title, 
		const sf::Vector2u& l_size);
	void Destroy();
	void Create();

	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_isDone;//window is closed?
	bool m_isFullScreen;

	EventManager m_eventManager;
	bool m_isFocused;
};

