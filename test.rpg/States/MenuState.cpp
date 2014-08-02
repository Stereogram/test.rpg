#include "StateMachine.hpp"
#include "MenuState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>
#include <iostream>
#include "../Game.hpp"

MenuState::MenuState(StateMachine& machine, sf::RenderWindow& window, bool replace, std::unique_ptr<Params> params)
: GameState(machine, window, replace)
, _params(new Params("MenuState"))
{
	_state = sf::Text("MenuState", *Game::Font);
	std::cout << "MenuState Init" << _params->State << std::endl;
}

void MenuState::pause()
{
	std::cout << "MenuState Pause" << std::endl;
}

void MenuState::resume(const std::unique_ptr<Params> params)
{
	std::cout << "MenuState Resume from " << params->State << std::endl;
}

void MenuState::update(const sf::Time dt)
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
						_machine.lastState(std::move(_params));
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