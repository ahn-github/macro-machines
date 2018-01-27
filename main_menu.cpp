#include "main_menu.hpp"
#include <iostream>
#include <vector>


namespace mm
{
    namespace MainMenu
    {
        MenuChoices display(sf::RenderWindow &window)
        {
            /*
             * Niin hyvää spagettia
             */

            sf::Font font;
            font.loadFromFile("fonts/Oxygen-Sans.ttf");
            sf::Vector2u winSize = window.getSize();

            sf::Text titleTxt("MacroMachines", font);
            titleTxt.setCharacterSize(60);
            titleTxt.setStyle(sf::Text::Bold);
            titleTxt.setColor(sf::Color::Red);
            sf::FloatRect textRect = titleTxt.getLocalBounds();
            titleTxt.setOrigin(textRect.left + textRect.width/2.0f,
                          textRect.top + textRect.height/2.0f);
            titleTxt.setPosition(sf::Vector2f(winSize.x/2.0f, winSize.y/10.0f));

            sf::Text mapTxt("Map (A)", font);
            mapTxt.setCharacterSize(30);
            mapTxt.setStyle(sf::Text::Bold);
            mapTxt.setColor(sf::Color::White);
            textRect = mapTxt.getLocalBounds();
            mapTxt.setOrigin(textRect.left + textRect.width/2.0f,
                             textRect.top + textRect.height/2.0f);
            mapTxt.setPosition(sf::Vector2f(winSize.x/2.0f, titleTxt.getPosition().y + 100.f));

            sf::Text mapTxt2("yeeeeee", font);
            mapTxt2.setCharacterSize(30);
            mapTxt2.setColor(sf::Color::White);
            mapTxt2.setPosition(sf::Vector2f(winSize.x/2.0f, titleTxt.getPosition().y + 150.f));

            sf::Text numPlayersTxt("Number of human players (S)", font);
            numPlayersTxt.setCharacterSize(30);
            numPlayersTxt.setStyle(sf::Text::Bold);
            numPlayersTxt.setColor(sf::Color::White);
            textRect = numPlayersTxt.getLocalBounds();
            numPlayersTxt.setOrigin(textRect.left + textRect.width/2.0f,
                                    textRect.top + textRect.height/2.0f);
            numPlayersTxt.setPosition(sf::Vector2f(winSize.x/2.0f, titleTxt.getPosition().y + 250.f));

            sf::Text numPlayersTxt2("yeeeeee", font);
            numPlayersTxt2.setCharacterSize(30);
            numPlayersTxt2.setColor(sf::Color::White);
            numPlayersTxt2.setPosition(sf::Vector2f(winSize.x/2.0f, titleTxt.getPosition().y + 300.f));

            sf::Text numAiTxt("Number of AI players (D)", font);
            numAiTxt.setCharacterSize(30);
            numAiTxt.setStyle(sf::Text::Bold);
            numAiTxt.setColor(sf::Color::White);
            textRect = numAiTxt.getLocalBounds();
            numAiTxt.setOrigin(textRect.left + textRect.width/2.0f,
                                    textRect.top + textRect.height/2.0f);
            numAiTxt.setPosition(sf::Vector2f(winSize.x/2.0f, titleTxt.getPosition().y + 400.f));

            sf::Text numAiTxt2("yeee", font);
            numAiTxt2.setCharacterSize(30);
            numAiTxt2.setColor(sf::Color::White);
            numAiTxt2.setPosition(sf::Vector2f(winSize.x/2.0f, titleTxt.getPosition().y + 450.f));

            sf::Text startTxt("The number of cars may not exceed 6.\nHit return to start the game!", font);
            startTxt.setCharacterSize(30);
            startTxt.setColor(sf::Color::Cyan);
            textRect = startTxt.getLocalBounds();
            startTxt.setOrigin(textRect.left + textRect.width/2.0f,
                               textRect.top + textRect.height/2.0f);
            startTxt.setPosition(sf::Vector2f(winSize.x/2.0f, titleTxt.getPosition().y + 650.f));

            std::vector<std::string> maps = {"Snake2.tmx", "Oscillator.tmx", "Oval.tmx"};
            MenuChoices choices = {.numAis = 1, .numHumans = 1, .mapName = maps[0]};
            auto it = maps.begin();

            sf::Event event;
            while(window.isOpen()) {
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) window.close();
                    if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::Return) return choices;
                        if (event.key.code == sf::Keyboard::Escape) window.close();
                        if (event.key.code == sf::Keyboard::A) {
                            ++it;
                            if(it == maps.end()) {
                                it = maps.begin();
                            }
                            choices.mapName = *it;
                        }
                        if (event.key.code == sf::Keyboard::S) {
                            if(choices.numHumans < 2 && choices.numHumans +
                                choices.numAis < 6) {
                                choices.numHumans += 1;
                            }
                            else
                                choices.numHumans = 0;
                        }
                        if (event.key.code == sf::Keyboard::D) {
                            if(choices.numHumans + choices.numAis < 6)
                                choices.numAis += 1;
                            else
                                choices.numAis = 0;
                        }
                    }
                }

                window.clear();

                mapTxt2.setString(choices.mapName);
                textRect = mapTxt2.getLocalBounds();
                mapTxt2.setOrigin(textRect.left + textRect.width/2.0f,
                              textRect.top + textRect.height/2.0f);

                numPlayersTxt2.setString(std::to_string(choices.numHumans));
                textRect = numPlayersTxt2.getLocalBounds();
                numPlayersTxt2.setOrigin(textRect.left + textRect.width/2.0f,
                              textRect.top + textRect.height/2.0f);

                numAiTxt2.setString(std::to_string(choices.numAis));
                textRect = numAiTxt2.getLocalBounds();
                numAiTxt2.setOrigin(textRect.left + textRect.width/2.0f,
                              textRect.top + textRect.height/2.0f);

                window.draw(titleTxt);
                window.draw(mapTxt);
                window.draw(mapTxt2);
                window.draw(numPlayersTxt);
                window.draw(numPlayersTxt2);
                window.draw(numAiTxt);
                window.draw(numAiTxt2);
                window.draw(startTxt);
                window.display();
            }

            return choices;
        }
    }
}
