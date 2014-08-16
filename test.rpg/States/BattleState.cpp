#include "BattleState.hpp"
#include "PlayState.hpp"
#include "StateMachine.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "../Game.hpp"

#include <iostream>
#include <memory>

BattleState::BattleState(StateMachine& machine, sf::RenderWindow& window, bool replace, std::unique_ptr<Params> params)
: GameState(machine, window, replace, std::move(params))
, _messages(3)
, _healthBox(sf::Color::Magenta, sf::Vector2f(Game::Size.x, Game::Size.y/5.f))
{
	_state = sf::Text("BattleState", *Game::Font);
	
	std::cout << "BattleState Init params:" << _params->State << std::endl;
	_params->State = "BattleState";

	_window.setView(_window.getDefaultView());

	_messages.setPosition(20.f, Game::Size.y - Game::Size.y / 4.f);
	_messages.add("testest");

}

void BattleState::pause()
{
	std::cout << "BattleState Pause" << std::endl;
}

void BattleState::resume(std::unique_ptr<Params> params)
{
	std::cout << "BattleState Resume from " << params->State << std::endl;
}

void BattleState::update(const sf::Time& dt)
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
					 _machine.lastState(std::move(_params));
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

void BattleState::draw() const
{
	// Clear the previous drawing
	_window.clear();
	_window.draw(_background);
	_window.draw(_healthBox);
	_window.draw(_messages);
	_window.draw(_state);
	_window.display();
}