#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "session.hpp"
#include "main_menu.hpp"
#include "winscreen.hpp"


int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Micromachines 1", sf::Style::Close);
	window.setFramerateLimit(60);
	while(window.isOpen()){
		mm::MainMenu::MenuChoices choices = mm::MainMenu::display(window);
		int winner = mm::Session::start(window, choices.mapName, choices.numHumans, choices.numAis);
		mm::WinScreen::display(window, winner);
	}
}
