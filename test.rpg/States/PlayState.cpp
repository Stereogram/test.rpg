#include <memory>
#include <iostream>

#include "StateMachine.hpp"
#include "PlayState.hpp"
#include "MenuState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

PlayState::PlayState( StateMachine& machine, sf::RenderWindow& window, bool replace )
: GameState( machine, window, replace )
{
	std::cout << "PlayState Init" << std::endl;
}

void PlayState::pause()
{
	std::cout << "PlayState Pause" << std::endl;
}

void PlayState::resume()
{
	std::cout << "PlayState Resume" << std::endl;
}

void PlayState::update(sf::Time dt)
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
						_machine.quit();
						break;

					case sf::Keyboard::M:
						_next = StateMachine::build<MenuState>( _machine, _window, false );
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

void PlayState::processEvents()
{

}


void PlayState::draw()
{
	// Clear the previous drawing
	_window.clear();
	_window.display();
}
