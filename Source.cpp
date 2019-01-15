#include "Game.hpp"

int main()
{
	Game game;
	char action;

	cout << "*****************GRA W ZYCIE!*****************" << endl;
	cout << "Czy chcesz podac dane startowe? (Y/N) ";
	cin.get(action);

	if (action == 'Y' || action == 'y')
		game.Recreate();

	game.Run();

	while (game.isRunning())
		game.Update();
}