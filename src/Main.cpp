#include "Platform/Platform.hpp"
#define CALC_Y(l, b) (l * b)
const int GAMEBOARD_SIZE = 1200;
const int LINE_THICKNESS = 50;

void drawBoard(sf::RenderWindow&);
std::vector<sf::RectangleShape> setupBoard();

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

	sf::Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					std::cout << "the right button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;
				}
			}
		}
		drawBoard(window);
	}

	return 0;
}

std::vector<sf::RectangleShape> setupBoard()
{
	std::vector<sf::RectangleShape> board_lines;
	for (int i = 0; i < 2; i++)
	{
		sf::RectangleShape line(sf::Vector2f(GAMEBOARD_SIZE, LINE_THICKNESS));
		line.setPosition(0, (i + 1) * GAMEBOARD_SIZE / 3 - 25);
		board_lines.push_back(line);
	}
	for (int i = 0; i < 2; i++)
	{
		sf::RectangleShape line(sf::Vector2f(LINE_THICKNESS, GAMEBOARD_SIZE));
		line.setPosition((i + 1) * GAMEBOARD_SIZE / 3 - 25, 0);
		board_lines.push_back(line);
	}
	return board_lines;
}

void drawBoard(sf::RenderWindow& mainGameWindow)
{
	mainGameWindow.clear();
	std::vector<sf::RectangleShape> board_lines = setupBoard();
	for (sf::Shape& line : board_lines)
		mainGameWindow.draw(line);
	mainGameWindow.display();
}
