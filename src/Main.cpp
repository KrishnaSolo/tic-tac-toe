#include "Platform/Platform.hpp"
const GAMEBOARD_SIZE = 1200;

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
	sf::RectangleShape horizontal_line_a(Vector2f(GAMEBOARD_SIZE, 100));
	horizontal_line_a.setPosition(0,GAMEBOARD_SIZE/3);
	
	sf::RectangleShape horizontal_line_b(Vector2f(GAMEBOARD_SIZE, 100));
	horizontal_line_b.setPosition(0,2*GAMEBOARD_SIZE/3);
	
	sf::RectangleShape vertical_line_a(Vector2f(100, GAMEBOARD_SIZE));
	vertical_line_a.setPosition(GAMEBOARD_SIZE/3, 0);
	
	sf::RectangleShape vertical_line_b(Vector2f(100, GAMEBOARD_SIZE));
	vertical_line_b.setPosition(2*GAMEBOARD_SIZE/3, 0);

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
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

		window.clear();
		window.draw(vertical_line_a);
		window.draw(vertical_line_b);
		window.draw(horizontal_line_a);
		window.draw(horizontal_line_b);
		window.display();
	}

	return 0;
}
