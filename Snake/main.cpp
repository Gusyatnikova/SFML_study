#include "Game.h"

int main() {
	Game game;
	while (!game.IsDone()) {
		game.HandleInput();
		game.Update();
		game.Render();
		game.RestartClock();	
	}
	while (!game.GetWindow()->IsDone()) {
		game.ShowGameOver();
		game.Update();
	}
	return 0;
}