#pragma once
#include <vector>
#include <unordered_map>
#include <functional>
#include "base_state.h"
#include "shared_context.h"

enum class StateType {
	Intro = 1, MainMenu, Game, Paused, GameOver, Credits
};

//map doesn't keep a stack-like order in container
using StateContainer = std::vector<std::pair<StateType, BaseState*>>;
using TypeContainer = std::vector<StateType>;
//function will generate a key type
using StateFactory = std::unordered_map<StateType, std::function<BaseState*()>>;

class StateManager {
private:
	//will be created in Game class 
	SharedContext* m_shared;
	StateContainer m_states;
	//because cannot remove a state in random moment: we kept it is remove when it not used
	TypeContainer m_toRemove;
	StateFactory m_stateFactory;

	void CreateState(const StateType &type);
	void RemoveState(const StateType &type);
	template<typename T>//T - type of class, derived from BaseState
	void RegisterState(const StateType &type) {
		m_stateFactory[type] = [this]() -> BaseState* {
			return new T(this);
		};
	}
public:
	StateManager(SharedContext *context);
	~StateManager();

	void Update(const sf::Time &time);
	void Draw();
	//It is called last in the game loop, which
	//ensures that the states in the m_toRemove container are no longer in use.
	void ProcessRequests();
	SharedContext* GetContext() { return m_shared; }
	bool HasState(const StateType &type) const;
	//change the current state to type
	void SwitchTo(const StateType &type);
	void Remove(const StateType &type);
};
