#include "Game.h"

int main() {
	Game game;
	while (!game.GetWindow()->IsDone()) {
		//game.HandleInput();
		game.Update();
		game.Render();
		//game.RestartClock();	
		game.LateUpdate();
	}
	return 0;
}