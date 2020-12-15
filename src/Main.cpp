#include "Platform/Platform.hpp"
#define CALC_LINE_POS(i) ((i + 1) * TILE_SIZE + 50 * i)

const int GAMEBOARD_SIZE = 1300;
const float DIAGONAL = 1838.47;
const int TILE_SIZE = 400;
const int LINE_THICKNESS = 50;
int TURN = 0;

sf::Color grey(128, 128, 128);
sf::Texture o_texture;
sf::Texture x_texture;

void drawBoard(sf::RenderWindow&);
std::vector<sf::RectangleShape> setupBoard();
std::vector<sf::RectangleShape> tiles;
std::vector<sf::RectangleShape> board_lines;

void checkWinner(sf::RenderWindow& gameWindow)
{
	//gameWindow.clear();
	if ((tiles[0].getTexture() == &o_texture || tiles[0].getTexture() == &x_texture) && tiles[0].getTexture() == tiles[1].getTexture() && tiles[1].getTexture() == tiles[2].getTexture())
	{
		sf::RectangleShape line(sf::Vector2f(GAMEBOARD_SIZE, LINE_THICKNESS));
		line.setPosition(0, 175);
		line.setFillColor(sf::Color::Red);
		gameWindow.draw(line);
	}
	else if ((tiles[3].getTexture() == &o_texture || tiles[3].getTexture() == &x_texture) && tiles[3].getTexture() == tiles[4].getTexture() && tiles[4].getTexture() == tiles[5].getTexture())
	{
		sf::RectangleShape line(sf::Vector2f(GAMEBOARD_SIZE, LINE_THICKNESS));
		line.setPosition(0, 625);
		line.setFillColor(sf::Color::Red);
		gameWindow.draw(line);
	}
	else if ((tiles[6].getTexture() == &o_texture || tiles[6].getTexture() == &x_texture) && tiles[6].getTexture() == tiles[7].getTexture() && tiles[7].getTexture() == tiles[8].getTexture())
	{
		sf::RectangleShape line(sf::Vector2f(GAMEBOARD_SIZE, LINE_THICKNESS));
		line.setPosition(0, 1075);
		line.setFillColor(sf::Color::Red);
		gameWindow.draw(line);
	}
	else if ((tiles[0].getTexture() == &o_texture || tiles[0].getTexture() == &x_texture) && tiles[0].getTexture() == tiles[3].getTexture() && tiles[3].getTexture() == tiles[6].getTexture())
	{
		sf::RectangleShape line(sf::Vector2f(LINE_THICKNESS, GAMEBOARD_SIZE));
		line.setPosition(175, 0);
		line.setFillColor(sf::Color::Red);
		gameWindow.draw(line);
	}
	else if ((tiles[1].getTexture() == &o_texture || tiles[1].getTexture() == &x_texture) && tiles[1].getTexture() == tiles[4].getTexture() && tiles[4].getTexture() == tiles[7].getTexture())
	{
		sf::RectangleShape line(sf::Vector2f(LINE_THICKNESS, GAMEBOARD_SIZE));
		line.setPosition(625, 0);
		line.setFillColor(sf::Color::Red);
		gameWindow.draw(line);
	}
	else if ((tiles[2].getTexture() == &o_texture || tiles[2].getTexture() == &x_texture) && tiles[2].getTexture() == tiles[5].getTexture() && tiles[5].getTexture() == tiles[8].getTexture())
	{
		sf::RectangleShape line(sf::Vector2f(LINE_THICKNESS, GAMEBOARD_SIZE));
		line.setPosition(1075, 0);
		line.setFillColor(sf::Color::Red);
		gameWindow.draw(line);
	}
	else if ((tiles[0].getTexture() == &o_texture || tiles[0].getTexture() == &x_texture) && tiles[0].getTexture() == tiles[4].getTexture() && tiles[4].getTexture() == tiles[8].getTexture())
	{
		sf::RectangleShape line(sf::Vector2f(DIAGONAL, LINE_THICKNESS));
		line.rotate(45.f);
		line.setFillColor(sf::Color::Red);
		gameWindow.draw(line);
	}
	else if ((tiles[2].getTexture() == &o_texture || tiles[2].getTexture() == &x_texture) && tiles[2].getTexture() == tiles[4].getTexture() && tiles[4].getTexture() == tiles[6].getTexture())
	{
		sf::RectangleShape line(sf::Vector2f(DIAGONAL, LINE_THICKNESS));
		line.rotate(135.f);
		line.setPosition(GAMEBOARD_SIZE, 0);
		line.setFillColor(sf::Color::Red);
		gameWindow.draw(line);
	}
	gameWindow.display();
}

void updateClickedTile(int x, int y)
{
	for (sf::RectangleShape& tile : tiles)
	{
		if (tile.getTexture() == NULL && tile.getGlobalBounds().contains(x, y))
		{
			if (!TURN)
			{
				tile.setTexture(&x_texture);
				TURN = !TURN;
			}
			else
			{
				tile.setTexture(&o_texture);
				TURN = !TURN;
			}
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

	sf::Event event;
	o_texture.loadFromFile("src/0.png");
	x_texture.loadFromFile("src/x.png");

	setupBoard();
	drawBoard(window);
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				updateClickedTile(event.mouseButton.x, event.mouseButton.y);
			}
		}
		drawBoard(window);
		checkWinner(window);
	}

	return 0;
}

std::vector<sf::RectangleShape> setupBoard()
{
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
		line.setPosition(0, CALC_LINE_POS(i));
		board_lines.push_back(line);
	}
	for (int i = 0; i < 2; i++)
	{
		sf::RectangleShape line(sf::Vector2f(LINE_THICKNESS, GAMEBOARD_SIZE));
		line.setPosition(CALC_LINE_POS(i), 0);
		board_lines.push_back(line);
	}
	return board_lines;
}

void drawBoard(sf::RenderWindow& mainGameWindow)
{
	mainGameWindow.clear();
	for (sf::Shape& line : board_lines)
		mainGameWindow.draw(line);
	for (sf::Shape& tile : tiles)
		mainGameWindow.draw(tile);
	mainGameWindow.display();
}
