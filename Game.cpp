#include "Game.hpp"

Game::Game()
	: windowWidth{ 800 }
	, windowHeight{ 600 }
	, cellSize{ 20 }
	, fps{ 15 }
	, randomStart{ true }
	, running{ false }
	, state{ MODIFYING }
	, trace{ true }
{
	srand(time(0));
	icon.loadFromFile("icon.png");

}


void Game::Run()
{
	
	window.create(VideoMode(windowWidth, windowHeight, 32), "Game of Life - creating", Style::Close);
	window.setIcon(44, 44, icon.getPixelsPtr());
	//window.setVerticalSyncEnabled(true); //automatyczne
	window.setFramerateLimit(fps); // rêczne
	window.requestFocus();
	FreeConsole();
	grid.create(windowWidth, windowHeight, cellSize, randomStart, trace);
	running = true;
}


void Game::Recreate()
{
	char action;

	do
	{
		cout << endl << "Wymiary okna musza byc podzielne przez rozmiar komorki!" << endl;
		cout << "Podaj szerokosc okna: ";
		cin >> windowWidth;
		cout << "Podaj wysokosc okna: ";
		cin >> windowHeight;
		cout << "Podaj rozmiar komorki: ";
		cin >> cellSize;

	} while (windowWidth%cellSize != 0 && windowHeight%cellSize != 0);

	//grid.setRes(windowWidth, windowHeight);
	cout << "Podaj liczbe klatek na sekunde: ";
	cin >> fps;

	cout << "Losowe wartosci poczatkowe? (Y/N) ";
	cin.clear();
	cin.ignore(10000, '\n');
	cin.get(action);
	if (action == 'Y' || action == 'y')
		randomStart = true;
	else randomStart = false;

	cout << "Pokazuj slad? (Y/N) ";
	cin.clear();
	cin.ignore(10000, '\n');
	cin.get(action);
	if (action == 'Y' || action == 'y')
		trace = true;
	else trace = false;

	

}

void Game::Update()
{
   	 
	while (window.isOpen())
	{
		if (state == MODIFYING)
			window.setTitle("Game of Life - modifying - " + std::to_string(fps) + " FPS");
		else
			window.setTitle("Game of Life - " + std::to_string(fps) + " FPS");
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) // zamkniecie okna krzyzykiem
				window.close();

			if (event.type == Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case Keyboard::Escape: // zamkniecie okna esc
					window.close();
					break;
				case Keyboard::Return: // zmiana stanu
				case Keyboard::Space:
					state = !state;
					break;
				case Keyboard::Add: // +5 fps
					fps += 5;
					fps > 60 ? fps = 60 : fps;
					window.setFramerateLimit(fps);
					break;
				case Keyboard::Subtract: // -5 fps
					fps -= 5;
					fps < 1 ? fps = 1 : fps;
					window.setFramerateLimit(fps);
					break;
				case Keyboard::Multiply: // +1 fps
					fps += 1;
					fps > 60 ? fps = 60 : fps;
					window.setFramerateLimit(fps);
					break;
				case Keyboard::Divide: // -1 fps
					fps -= 1;
					fps < 1 ? fps = 1 : fps;
					window.setFramerateLimit(fps);
					break;
					//	case Keyboard::E: // czyszczenie pojedynczej kratki
					//		if (state == MODIFYING)
					//		{
					//			int x = Mouse::getPosition(window).x / cellSize;
					//			int y = Mouse::getPosition(window).y / cellSize;
					//			grid.setCell(false, x, y);
					//			grid.setVisited(false, x, y);
					//		}
					//		break;
				case Keyboard::C: // czyszczenie calej planszy
					if (state == MODIFYING)
						for (int x = 0; x < windowWidth / cellSize; x++)
							for (int y = 0; y < windowHeight / cellSize; y++)
							{
								grid.setCell(false, x, y);
								grid.setVisited(false, x, y);
							}
					break;
				case Keyboard::R: // losowanie pol
					if (state == MODIFYING)
						grid.randomize();
					break;

				case Keyboard::F1: // glider
					if (state == MODIFYING)
						grid.spawn(Pattern::glider, (Mouse::getPosition(window).x / cellSize), (Mouse::getPosition(window).y / cellSize));
					break;
				case Keyboard::F2: // blinker
					if (state == MODIFYING)
						grid.spawn(Pattern::blinker, (Mouse::getPosition(window).x / cellSize), (Mouse::getPosition(window).y / cellSize));
					break;
				case Keyboard::F3: // dakota
					if (state == MODIFYING)
						grid.spawn(Pattern::dakota, (Mouse::getPosition(window).x / cellSize), (Mouse::getPosition(window).y / cellSize));
					break;
				case Keyboard::F4: // gosper
					if (state == MODIFYING)
						grid.spawn(Pattern::gosper, (Mouse::getPosition(window).x / cellSize), (Mouse::getPosition(window).y / cellSize));
					break;
				case Keyboard::F5: // rpentomino
					if (state == MODIFYING)
						grid.spawn(Pattern::rpent, (Mouse::getPosition(window).x / cellSize), (Mouse::getPosition(window).y / cellSize));
					break;
				case Keyboard::F6: // krokodyl
					if (state == MODIFYING)
						grid.spawn(Pattern::croc, (Mouse::getPosition(window).x / cellSize), (Mouse::getPosition(window).y / cellSize));
					break;
				case Keyboard::F7: // fontanna
					if (state == MODIFYING)
						grid.spawn(Pattern::fountain, (Mouse::getPosition(window).x / cellSize), (Mouse::getPosition(window).y / cellSize));
					break;
				case Keyboard::F8: // copperhead
					if (state == MODIFYING)
						grid.spawn(Pattern::copperhead, (Mouse::getPosition(window).x / cellSize), (Mouse::getPosition(window).y / cellSize));
					break;
				default:
					break;
				}
			}


			if (event.type == Event::MouseButtonPressed && state == MODIFYING)
				if (event.mouseButton.button == Mouse::Left) // zmiana stanu na przeciwny
				{
					int x = Mouse::getPosition(window).x / cellSize;
					int y = Mouse::getPosition(window).y / cellSize;

					if (x >= 0 && y >= 0 && x <= windowWidth / cellSize - 1 && y <= windowHeight / cellSize - 1)
						grid.setCell(!grid.isCellAlive(x, y), x, y);
				}
				else if ((event.mouseButton.button == Mouse::Right)) // czyszczenie pojedynczej kratki
				{
					int x = Mouse::getPosition(window).x / cellSize;
					int y = Mouse::getPosition(window).y / cellSize;

					if (x >= 0 && y >= 0 && x <= windowWidth / cellSize - 1 && y <= windowHeight / cellSize - 1)
						grid.setCell(false, x, y);
					grid.setVisited(false, x, y);
				}





			if (event.type == Event::MouseMoved && state == MODIFYING) // ciagla zmiana LPM
				if (Mouse::isButtonPressed(Mouse::Left))
				{


					int x = Mouse::getPosition(window).x / cellSize;
					int y = Mouse::getPosition(window).y / cellSize;

					if (x >= 0 && y >= 0 && x <= windowWidth / cellSize - 1 && y <= windowHeight / cellSize - 1)
						grid.setCell(!grid.isCellAlive(x, y), x, y);

				}
		}

		if (state == UPDATING)
			grid.update();

		window.clear(Color::White);
		grid.draw(window);
		window.display();

	}

	running = false;


}

bool Game::isRunning()
{
	return running;
}
