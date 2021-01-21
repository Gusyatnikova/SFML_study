#pragma once
#include "Window.h"
#include "event_manager.h"

struct SharedContext {
	Window* m_wnd;
	EventManager* m_eventManager;
	SharedContext()
		: m_wnd(nullptr), m_eventManager(nullptr) {}
};