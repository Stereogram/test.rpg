#include "StateMachine.hpp"
#include "MenuState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>
#include <iostream>
#include "../Game.hpp"

MenuState::MenuState( StateMachine& machine, sf::RenderWindow& window, bool replace )
: GameState( machine, window, replace )
{
	_state = sf::Text("MenuState", *Game::Font);
	std::cout << "MenuState Init" << std::endl;
}

void MenuState::pause()
{
	std::cout << "MenuState Pause" << std::endl;
}

void MenuState::resume()
{
	std::cout << "MenuState Resume" << std::endl;
}

void MenuState::update(sf::Time dt)
{
	sf::Event event;

	while( _window.pollEvent( event ) )
	{
		switch( event.type )
		{
			case sf::Event::Closed:
				_machine.quit();
				break;

			case sf::Event::KeyPressed:
				switch( event.key.code )
				{
					case sf::Keyboard::Escape:
						_machine.lastState();
						break;

					default:
						break;
				}
				break;

			default:
				break;
		}
	}
}

void MenuState::processEvents()
{

}

void MenuState::draw()
{
	// Clear the previous drawing
	_window.clear();
	_window.draw(_state);
	_window.display();
}
