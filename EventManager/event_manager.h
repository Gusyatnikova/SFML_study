#pragma once

#include <vector>
#include <unordered_map>

#include "SFML/Window.hpp"

enum class EventType {
	KeyDown = sf::Event::KeyPressed,
	KeyUp = sf::Event::KeyReleased,
	MButtonUp = sf::Event::MouseButtonPressed,
	MButtonDown = sf::Event::MouseButtonReleased,
	MouseWheel = sf::Event::MouseWheelMoved,
	WindowResized = sf::Event::Resized,
	GainedFocus = sf::Event::GainedFocus,
	LostFocus = sf::Event::LostFocus,
	MouseEntered = sf::Event::MouseEntered,
	MouseLeft = sf::Event::MouseLeft,
	Closed = sf::Event::Closed,
	TextEntered = sf::Event::TextEntered,
	Keyboard = sf::Event::Count + 1, Mouse, Joystick
};

struct EventInfo {
	//EventInfo() { m_code = 0; }
	//EventInfo(int l_event = 0) { m_code = l_event; }
	EventInfo(int l_event = 0) : m_code(l_event) {}
	union {
		int m_code;
	};
};

using Events = std::vector<std::pair<EventType, EventInfo>>;

struct EventDetails {
	EventDetails(const std::string& bindName) {
		m_name = bindName;
		Clear();
	}

	std::string m_name;
	sf::Vector2i m_size;
	sf::Uint32 m_textEntered;
	sf::Vector2i m_mouse;
	int m_mouseWheelDelta;
	int m_keyCode;

	void Clear() {
		m_size = { 0, 0 };
		m_textEntered = 0;
		m_mouse = { 0, 0 };
		m_mouseWheelDelta = 0;
		m_keyCode = -1;
	}
};

struct Binding {
	Binding(const std::string& name)
		: m_name(name), m_events_occured(0), m_details(name) {}
	void BindEvent(EventType event_type, EventInfo event_info = EventInfo()) {
		m_events.emplace_back(event_type, event_info);
		//m_events.push_back(std::make_pair(event_type, event_info));
	}
	Events m_events;
	std::string m_name;
	int m_events_occured;
	EventDetails m_details;
};

using Bindings = std::unordered_map<std::string, Binding*>;
//-------------------------76---------------------------------//


