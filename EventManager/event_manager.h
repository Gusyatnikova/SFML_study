#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <functional>
#include "SFML/Graphics.hpp"

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

class EventDetails {
public:
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
	Binding(const std::string& name = "")
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

//eventName -> Callback func
using CallbackContainer = std::unordered_map<
	std::string, std::function<void(EventDetails*)>>;
//for each state one map of callbacks
enum class StateType;
using Callbacks = std::unordered_map
	<StateType, CallbackContainer>;

class EventManager {
private:
	Bindings m_bindings;
	Callbacks m_callbacks;
	bool m_hasFocus;
	StateType m_currentState;

	void LoadBindings();
public:
	EventManager();
	~EventManager();

	bool AddBinding(Binding *binding);
	bool RemoveBinding(const std::string &name);

	void SetFocus(bool focus) { m_hasFocus = focus; }

	template <typename T>
	bool AddCallback(StateType state, const std::string &name,
		void (T::*func)(EventDetails*), T* instance) {
		auto it = m_callbacks.emplace(state, CallbackContainer()).first;
		//бинд так управл€ет аргументами функции _1 означает первый параметр
		//если foo(int, int) и f = bind(foo, 101, _1), то f(-10) = foo(101, -10)
		//сколько указать заполнителей _num, столько и будет нужно аргументов при вызове f
		auto tmp = std::bind(func, instance, std::placeholders::_1);
		//emplace return std::pair<std::iterator, bool> 1-ый ук-ет на позицию вставленного эл-та
		//или сущ-й эл-т если вставки не было. 2-й = 1, если вставка была, иначе 0
		//return m_callbacks.emplace(name, tmp).second;
		return it->second.emplace(name, tmp).second;
	}

	bool RemoveCallback(StateType state, const std::string &name);

	void HandleEvent(const sf::Event& event);
	void Update();
	sf::Vector2i GetMousePosition(sf::RenderWindow* wnd = nullptr) {
		return wnd ? sf::Mouse::getPosition(*wnd)
			: sf::Mouse::getPosition();
	}
	void SetCurrentState(StateType state) { m_currentState = state; }
};



