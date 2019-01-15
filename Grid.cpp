#include "Grid.hpp"
using namespace sf;


void Grid::create(int width_, int height_, int size, bool randomStart, bool trace_)
{
	sizeOfCell = size;
	trace = trace_;
	width = width_ / sizeOfCell;
	height = height_ / sizeOfCell;

	cells = new Cell*[width];

	for (int x = 0; x < width; x++)
	{
		cells[x] = new Cell[height];
		for (int y = 0; y < height; y++)
		{
			cells[x][y] = Cell(x * sizeOfCell, y * sizeOfCell, false, sizeOfCell, trace);
		}
	}
	if (randomStart)
		randomize();
}

Grid::~Grid()
{
	for (int x = 0; x < width; x++)
		delete[] cells[x];
	delete[] cells;
}

void Grid::setCell(bool alive, int x, int y)
{
	cells[x][y].setAlive(alive);
	if (alive)
		cells[x][y].setVisited(true);
}

bool Grid::isCellAlive(int x, int y)
{
	return cells[x][y].isAlive();
}

void Grid::update()
{
	bool **cellsToDie = new bool*[width];
	bool **cellsToBorn = new bool*[width];

	for (int x = 0; x < width; x++)
	{
		cellsToDie[x] = new bool[height];
		cellsToBorn[x] = new bool[height];
	}

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			cellsToDie[x][y] = false;
			cellsToBorn[x][y] = false;
		}
	}

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			if (cells[x][y].isAlive())
				cells[x][y].setVisited(true);

			int near{ 0 };

			near += cells[(x - 1 + width) % width][(y - 1 + height) % height].isAlive();
			near += cells[(x - 1 + width) % width][y].isAlive();
			near += cells[(x - 1 + width) % width][(y + 1 + height) % height].isAlive();

			near += cells[x][(y - 1 + height) % height].isAlive();
			near += cells[x][(y + 1 + height) % height].isAlive();

			near += cells[(x + 1 + width) % width][(y - 1 + height) % height].isAlive();
			near += cells[(x + 1 + width) % width][y].isAlive();
			near += cells[(x + 1 + width) % width][(y + 1 + height) % height].isAlive();

			if (cells[x][y].isAlive())
			{
				if (near != 2 && near != 3)
					cellsToDie[x][y] = true;
			}
			else
			{
				if (near == 3)
					cellsToBorn[x][y] = true;
			}
		}
	}

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			if (cellsToDie[x][y])
				cells[x][y].setAlive(false);

			if (cellsToBorn[x][y])
				cells[x][y].setAlive(true);
		}
	}

	for (int x = 0; x < width; x++)
	{
		delete[] cellsToBorn[x];
		delete[] cellsToDie[x];
	}

	delete[] cellsToBorn;
	delete[] cellsToDie;
}

void Grid::draw(RenderWindow &window)
{
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			cells[x][y].draw(window);
}

void Grid::randomize()
{
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			cells[x][y] = Cell(x * sizeOfCell, y * sizeOfCell, !bool(rand() % 3), sizeOfCell, trace);

}

void Grid::setVisited(bool visited, int x, int y)
{
	cells[x][y].setVisited(visited);
}

void Grid::spawn(int number, int x_, int y_)
{
	for (int x = 0; x < pattern.seed[number].size(); x++)
	{
		for (int y = 0; y < pattern.seed[number][x].size(); y++)
		{
			cells[(x_ + y + width) % width][(y_ + x + height) % height].setAlive(pattern.seed[number][x][y]);
			if (cells[(x_ + y + width) % width][(y_ + x + height) % height].isAlive())
				cells[(x_ + y + width) % width][(y_ + x + height) % height].setVisited(true);
		}
	}
}
