#include "Window.h"

Window::Window() {
	Setup("Window", sf::Vector2u(640, 480));
}

Window::Window(const std::string& l_title, const sf::Vector2u& l_size) {
	Setup(l_title, l_size);
}

Window::~Window() {
	Destroy();
}

void Window::Setup(const std::string& l_title, const sf::Vector2u& l_size) {
	m_windowTitle = l_title;
	m_windowSize = l_size;
	m_isFullScreen = false;
	m_isDone = false;
	Create();
	//m_window.setFramerateLimit(60);//60 FPS cap - max fpr in sec
	m_isFocused = true;
	/*m_eventManager.AddCallback("Fullscreen_toggle",
		&Window::ToggleFullScreen, this);
	m_eventManager.AddCallback("Window_close",
		&Window::Close, this);*/
}

void Window::Create() {
	//style is sf::Uint32
	auto style = (m_isFullScreen ?
		sf::Style::Fullscreen : sf::Style::Default);
	m_window.create(sf::VideoMode(m_windowSize.x, m_windowSize.y, 32),
		m_windowTitle, style);
}

void Window::Destroy() {
	m_window.close();
}

void Window::Update() {
	sf::Event event;
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::LostFocus) {
			m_isFocused = false;
			m_eventManager.SetFocus(false);
		}
		else if (event.type == sf::Event::GainedFocus) {
			m_isFocused = true;
			m_eventManager.SetFocus(true);
		}
		//
		m_eventManager.HandleEvent(event);
	}
	//real-time events 
	m_eventManager.Update();
}

//void Window::Close() {
//	Destroy();
//}

void Window::Close(EventDetails *details) { m_isDone = true;  }

void Window::ToggleFullScreen(EventDetails *details) {
	m_isFullScreen = !m_isFullScreen;
	Destroy();
	Create();
}

void Window::BeginDraw() {
	m_window.clear(sf::Color::Black);
}

void Window::EndDraw() {
	m_window.display();
}

bool Window::IsDone() const {
	return m_isDone;
}

bool Window::IsFullScreen() const {
	return m_isFullScreen;
}

bool Window::IsFocused() const { return m_isFocused; }

void Window::Draw(sf::Drawable& l_drawable) {
	m_window.draw(l_drawable);
}

sf::Vector2u Window::GetWindowSize() const {
	return m_windowSize;
}

sf::RenderWindow* Window::GetRenderWindow() {
	return &m_window;
}

EventManager* Window::GetEventManager() { return &m_eventManager; }