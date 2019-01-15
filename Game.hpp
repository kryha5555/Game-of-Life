#pragma once
#include <iostream>
#include <ctime>
#include <SFML/Window.hpp>
#include <Windows.h>
#include "Grid.hpp"

using namespace std;
using namespace sf;


class Game
{
private:
	bool running;
	int windowWidth;
	int windowHeight;
	int cellSize;
	int fps;
	bool randomStart;
	bool state;
	bool trace;
	char action;
	Image icon;
	RenderWindow window;
	Event event;
	Grid grid;
	
	enum
	{
		UPDATING,
		MODIFYING
	};
	

public:
	Game();
	void Run();
	void Recreate();
	void Update();
	bool isRunning();
};

