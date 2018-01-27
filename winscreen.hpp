#ifndef MM_WIN_SCREEN_H
#define MM_WIN_SCREEN_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>


namespace mm
{
	namespace WinScreen
	{
		void display(sf::RenderWindow &window, int winner);
	};
}

#endif
