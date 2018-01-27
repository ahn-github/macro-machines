#include "winscreen.hpp"
#include <iostream>
#include <vector>


namespace mm
{
	namespace WinScreen
	{	
		//Logic for the winning screen
		void display(sf::RenderWindow &window, int winner)
		{ 
			std::string imagename = "maps/";
			if (winner == 1)
				imagename += "winner.jpg";
			else
				imagename += "loser.jpg";

			window.clear();

			sf::Texture texture;
			if (texture.loadFromFile(imagename) != true)
			{
				return;
			}

			sf::Sprite sprite(texture);
			sprite.setPosition(sf::Vector2f(window.getSize().x/2 - texture.getSize().x/2, window.getSize().y/2 - texture.getSize().y/2));
			window.clear();
			window.draw(sprite, sf::RenderStates::Default);
			window.display();

			sf::Event event;
			while (window.isOpen()) {
				while (window.pollEvent(event)) {
					if (event.type == sf::Event::Closed) window.close();
					if (event.type == sf::Event::KeyPressed) {
						if (event.key.code == sf::Keyboard::Return) return;
						if (event.key.code == sf::Keyboard::Escape) window.close();
					}
				}
			}

			return;
		}
	}
}
