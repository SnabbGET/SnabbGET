// Graphic User Interface

/**
 * @file src/interface/gui.cpp
 * @brief GUI file of the project.
 * @author LAPCoder
 * @version 0.0.0
 * 
 * MIT License
 */

#include <iostream>
#include <SFML/Graphics.hpp>

// https://sourceforge.net/projects/cpptk/files/

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 300), "SnabbGET");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	sf::Font cascadia_code;

	// Load from a font file on disk
	if (!cascadia_code.loadFromFile("fonts/cascadia-code/CascadiaCode.ttf"))
	{
		// Error...
		#ifdef DEBUG
			std::cout << "Error loading font" << std::endl;
		#endif
		exit(EXIT_FAILURE);
	}

	sf::Text Text;
	Text.setFont(cascadia_code);
	Text.setString(L"Hello World");
	Text.setCharacterSize(24);
	Text.setStyle(sf::Text::Regular);
	Text.setFillColor(sf::Color::Red);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::Resized)
			{
				std::cout << "new width: " << event.size.width << std::endl;
				std::cout << "new height: " << event.size.height << std::endl;
			}
		}

		//window.setSize({window.getSize().x, window.getSize().y});

		Text.setCharacterSize(24);

		window.clear();
		window.draw(shape);
		window.draw(Text);
		window.display();
	}

	return 0;
}