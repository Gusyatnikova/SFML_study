#include "state_manager.h"
#include "state_mainMenu.h"
#include "state_game.h"
#include "state_game_over.h"

StateManager::StateManager(SharedContext *context)
	: m_shared(context) {
	RegisterState<State_MainMenu>(StateType::MainMenu);
	RegisterState<State_Game>(StateType::Game);
	RegisterState<State_GameOver>(StateType::GameOver);
}

StateManager::~StateManager() {
	for (auto &it : m_states) {
		it.second->OnDestroy();
		delete it.second;
	}
}

void StateManager::Draw() {
	if (m_states.empty()) return;
	if (m_states.back().second->IsTransparent()
		&& m_states.size() > 1) {
		auto it = m_states.end();
		while (it != m_states.begin()) {
			if (it != m_states.end()) {
				if (!it->second->IsTransparent()) break;
			}
			--it;
		}
		for (; it != m_states.end(); ++it) {
			it->second->Draw();
		}
	}
	else {
		m_states.back().second->Draw();
	}
}

void StateManager::Update(const sf::Time &time) {
	if (m_states.empty()) return;
	if (m_states.back().second->IsTranscendent()
		&& m_states.size() > 1) {
		auto it = m_states.end();
		while (it != m_states.begin()) {
			if (it != m_states.end()) {
				if (!it->second->IsTranscendent()) break;
			}
			--it;
		}
		for (; it != m_states.end(); ++it) {
			it->second->Update(time);
		}
	}
	else {
		m_states.back().second->Update(time);
	}
}

bool StateManager::HasState(const StateType &type) const {
	for (auto it = m_states.begin(); it != m_states.end(); ++it) {
		if (it->first == type) {
			auto removed = std::find(
				m_toRemove.begin(), m_toRemove.end(), type);
			if (removed == m_toRemove.end()) return true;
			return false;
		}
	}
	return false;
}

void StateManager::ProcessRequests() {
	while (!m_toRemove.empty()) {
		RemoveState(*m_toRemove.begin());
		m_toRemove.erase(m_toRemove.begin());
	}
}

void StateManager::SwitchTo(const StateType &type) {
	m_shared->m_eventManager->SetCurrentState(type);
	for (auto it = m_states.begin(); it != m_states.end(); ++it) {
		if (it->first == type) {
			m_states.back().second->Deactivate();
			StateType tmp_type = it->first;
			BaseState *tmp_state = it->second;
			m_states.erase(it);
			m_states.emplace_back(tmp_type, tmp_state);
			tmp_state->Activate();
			return;
		}
	}
	if (!m_states.empty()) m_states.back().second->Deactivate();
	CreateState(type);
	m_states.back().second->Activate();
}

void StateManager::CreateState(const StateType &type) {
	auto newState = m_stateFactory.find(type);
	if (newState == m_stateFactory.end()) return;
	BaseState *state = newState->second();
	m_states.emplace_back(type, state);
	state->OnCreate();
}

void StateManager::Remove(const StateType& l_type) {
	m_toRemove.push_back(l_type);
}

void StateManager::RemoveState(const StateType &type) {
	for (auto it = m_states.begin(); it != m_states.end(); ++it) {
		if (it->first == type) {
			it->second->OnDestroy();
			delete it->second;
			m_states.erase(it);
			return;
		}
	}
}

