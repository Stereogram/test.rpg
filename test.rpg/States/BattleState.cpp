#include "BattleState.hpp"
#include "PlayState.hpp"
#include "StateMachine.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "../Game.hpp"

#include <iostream>
#include <memory>

BattleState::BattleState(StateMachine& machine, sf::RenderWindow& window, bool replace)
: GameState(machine, window, replace)
{
	_state = sf::Text("BattleState", *Game::Font);
	std::cout << "BattleState Init" << std::endl;
}

void BattleState::pause()
{
	std::cout << "BattleState Pause" << std::endl;
}

void BattleState::resume()
{
	std::cout << "BattleState Resume" << std::endl;
}

void BattleState::update(const sf::Time dt)
{
	sf::Event event;

	while (_window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				_machine.quit();
				break;

			case sf::Event::KeyPressed:
			{
				switch (event.key.code)
				{
				 case sf::Keyboard::Space:
					_next = StateMachine::build<PlayState>(_machine, _window, true);
					break;

				 case sf::Keyboard::Escape:
					_machine.quit();
					break;

				 default:
					break;
				}
				break;
			}

			default:
				break;
		}
	}
}

void BattleState::processEvents()
{

}

void BattleState::draw()
{
	// Clear the previous drawing
	_window.clear();
	_window.draw(_state);
	_window.display();
}
