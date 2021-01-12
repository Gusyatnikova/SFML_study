#pragma once
#include "Window.h"

class StateManager;

class BaseState {
private:
	friend class StateManager;
protected:
	StateManager *m_stateManager;
	//is state needs to render or update a state that came after it
	bool m_transparent;
	//The state's transcendence flag is checked first, in order to determine whether the
	//top state allows others to be updated (rendered) for transparent flag
	bool m_transcendent;
public:
	BaseState(StateManager *stateManager)
		: m_stateManager(stateManager),
		m_transparent(false), m_transcendent(false) {}
	virtual ~BaseState() {}
	//when state is created and pushed to the stack
	virtual void OnCreate() = 0;
	//when state is poped from the stack
	virtual void OnDestroy() = 0;
	//called once a state is moved to the top of the stack
	virtual void Activate() = 0;
	//called once a state is removed from the top position
	virtual void Deactivate() = 0;
	virtual void Update(const sf::Time &time) = 0;
	virtual void Draw() = 0;

	void SetTransparent(bool t) { m_transparent = t; }
	bool IsTransparent() const { return m_transparent; }
	void SetTranscedent(bool t) { m_transcendent = t; }
	bool IsTranscendent() const { return m_transcendent; }
	StateManager* GetStateManager() { return m_stateManager; }
};
//p.115