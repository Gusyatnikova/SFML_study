#include "event_manager.h"
#include <fstream>
#include <iostream>
#include <sstream>

EventManager::EventManager()
	: m_hasFocus(true) {
	LoadBindings();
}

EventManager::~EventManager() {
	for (auto &it : m_bindings) {
		delete it.second;
		it.second = nullptr;
	}
}

bool EventManager::AddBinding(Binding *bind) {
	if (m_bindings.find(bind->m_name) != m_bindings.end())
		return false;
	return m_bindings.emplace(bind->m_name, bind).second;
}

bool EventManager::RemoveBinding(const std::string &name) {
	auto it = m_bindings.find(name);
	if (m_bindings.end() == it) return false;
	delete it->second;
	m_bindings.erase(it);
	return true;
}

void EventManager::HandleEvent(const sf::Event &event) {
	//for Ctrl+Alt+Del Del check here
	for (auto& b_it : m_bindings) {
		Binding *bind = b_it.second;
		for (auto& event_it : bind->m_events) {
			EventType sfml_event = (EventType)event.type;
			if (event_it.first != sfml_event) continue;
			if (sfml_event == EventType::KeyUp ||
				sfml_event == EventType::KeyDown) {
				if (event_it.second.m_code == event.key.code) {
					if (bind->m_details.m_keyCode != -1) {
						bind->m_details.m_keyCode = event_it.second.m_code;
					}
					++(bind->m_events_occured);
					break;
				}
			}
			else if (sfml_event == EventType::MButtonDown ||
				sfml_event == EventType::MButtonUp) {
				if (event_it.second.m_code == event.mouseButton.button) {
					bind->m_details.m_mouse.x = event.mouseButton.x;
					bind->m_details.m_mouse.y = event.mouseButton.y;
					if (bind->m_details.m_keyCode != -1) {
						bind->m_details.m_keyCode = event_it.second.m_code;
					}
					++(bind->m_events_occured);
					break;
				}
			}
			else {
				if (sfml_event == EventType::MouseWheel) {
					bind->m_details.m_mouseWheelDelta =
						event.mouseWheel.delta;
				}
				else if (sfml_event == EventType::WindowResized) {
					bind->m_details.m_size.x = event.size.width;
					bind->m_details.m_size.y = event.size.height;
				}
				else if (sfml_event == EventType::TextEntered) {
					bind->m_details.m_textEntered = event.text.unicode;
				}
				++(bind->m_events_occured);
			}
		}
	}
}

//real-time input
//for Ctrl+Alt+Del Ctrl and Alt check here
void EventManager::Update() {
	if (!m_hasFocus) return;
	for (auto &b_it : m_bindings) {
		Binding *bind = b_it.second;
		for (auto &event_it : bind->m_events) {
			switch (event_it.first)
			{
			case (EventType::Keyboard):
				if (sf::Keyboard::isKeyPressed(
					sf::Keyboard::Key(event_it.second.m_code))) {
					if (bind->m_details.m_keyCode != -1) {
						bind->m_details.m_keyCode = event_it.second.m_code;
					}
					++(bind->m_events_occured);
				}
				break;
			case EventType::Mouse:
				if (sf::Mouse::isButtonPressed(
					sf::Mouse::Button(event_it.second.m_code))) {
					if (bind->m_details.m_keyCode != -1) {
						bind->m_details.m_keyCode = event_it.second.m_code;
					}
					++(bind->m_events_occured);
				}
				break;
			case EventType::Joystick:
				break;
			default:
				break;
			}
		}
		if (bind->m_events.size() == bind->m_events_occured) {
			auto call_itr = m_callbacks.find(bind->m_name);
			if (call_itr != m_callbacks.end()) {
				call_itr->second(&bind->m_details);
			}
		}
		bind->m_events_occured = 0;
		bind->m_details.Clear();
	}
}

void EventManager::LoadBindings() {
	std::string delimeter = ":";
	std::ifstream bindings;
	bindings.open("keys.cfg");
	if (!bindings.is_open()) {
		std::cout << "! Failed loading keys.cfg.\n";
		return;
	}
	std::string line;
	while (std::getline(bindings, line)) {
		std::stringstream keystream(line);
		std::string callbackName;
		keystream >> callbackName;
		Binding *bind = new Binding(callbackName);
		while (!keystream.eof()) {
			std::string keyval;
			keystream >> keyval;
			int start = 0;
			int end = keyval.find(delimeter);
			if (end == std::string::npos) {
				delete bind;
				bind = nullptr;
				break;
			}
			EventType type = EventType(
				std::stoi(keyval.substr(start, end - start)));
			int code = std::stoi(keyval.substr(end + delimeter.length(),
				keyval.find(delimeter, end + delimeter.length())));
			EventInfo event_info;
			event_info.m_code = code;
			bind->BindEvent(type, event_info);
		}
		if (!AddBinding(bind)) { delete bind; }
		bind = nullptr;
	}
	bindings.close();
}
