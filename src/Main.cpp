#include "Platform/Platform.hpp"
#define CALC_Y(l, b) (l * b)
const int GAMEBOARD_SIZE = 1300;
const int TILE_SIZE = 400;
const int LINE_THICKNESS = 50;
sf::Color grey(128, 128, 128);

void drawBoard(sf::RenderWindow&);
std::vector<sf::RectangleShape> setupBoard();
std::vector<sf::RectangleShape> tiles;

void updateClickedTile(int x, int y, sf::RenderWindow& window)
{
	for (sf::Shape& tile : tiles)
	{
		if (tile.getLocalBounds().contains(x, y))
		{
			tile.setFillColor(sf::Color::Green);
			window.draw(tile);
			window.display();
			return;
		}
	}
}

int main()
{
	util::Platform platform;

#if defined(_DEBUG)
	std::cout << "Debug Mode" << std::endl;
#endif

	sf::RenderWindow window;
	// in Windows at least, this must be called before creating the window
	float screenScalingFactor = platform.getScreenScalingFactor(window.getSystemHandle());
	// Use the screenScalingFactor
	window.create(sf::VideoMode(GAMEBOARD_SIZE * screenScalingFactor, GAMEBOARD_SIZE * screenScalingFactor), "Tic-Tac-Toe");

	drawBoard(window);
	sf::Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				updateClickedTile(event.mouseButton.x, event.mouseButton.y, window);
			}
		}
	}

	return 0;
}

std::vector<sf::RectangleShape> setupBoard()
{
	std::vector<sf::RectangleShape> board_lines;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			sf::RectangleShape tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));
			tile.setFillColor(grey);
			tile.setPosition(j * 450, i * 450);
			tiles.push_back(tile);
		}
	}

	for (int i = 0; i < 2; i++)
	{
		sf::RectangleShape line(sf::Vector2f(GAMEBOARD_SIZE, LINE_THICKNESS));
		line.setPosition(0, (i + 1) * TILE_SIZE + 50 * i);
		board_lines.push_back(line);
	}
	for (int i = 0; i < 2; i++)
	{
		sf::RectangleShape line(sf::Vector2f(LINE_THICKNESS, GAMEBOARD_SIZE));
		line.setPosition((i + 1) * TILE_SIZE + 50 * i, 0);
		board_lines.push_back(line);
	}
	return board_lines;
}

void drawBoard(sf::RenderWindow& mainGameWindow)
{
	mainGameWindow.clear();
	std::vector<sf::RectangleShape> board_shapes = setupBoard();
	for (sf::Shape& shape : board_shapes)
		mainGameWindow.draw(shape);
	for (sf::Shape& tile : tiles)
		mainGameWindow.draw(tile);
	mainGameWindow.display();
}
