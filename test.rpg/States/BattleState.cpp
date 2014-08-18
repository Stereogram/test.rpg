#include <iostream>
#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "../Game.hpp"
#include "BattleState.hpp"
#include "PlayState.hpp"
#include "StateMachine.hpp"
#include "../Params/Params.hpp"

BattleState::BattleState(StateMachine& machine, sf::RenderWindow& window, bool replace, std::unique_ptr<Params> params)
: GameState(machine, window, replace, std::move(params))
, _messages(3)
, _healthBox(sf::Color::Magenta, sf::Vector2f(static_cast<float>(Game::Size.x), Game::Size.y/5.f))
{
	_state = sf::Text("BattleState", *Game::Font);
	
	std::cout << "BattleState Init params:" << _params->State << std::endl;
	_params->State = "BattleState";

	_window.setView(_window.getDefaultView());

	_messages.setPosition(20.f, Game::Size.y - Game::Size.y / 4.f);
	_messages.add("testest");

	merge();
	while (!_queue.empty())
	{
		std::cout << _queue.front()->Name << std::endl;
		_queue.pop();
	}

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

void BattleState::merge()
{
	auto enemies = *dynamic_cast<BattleParams*>(_params.get())->Enemies;
	auto party = *_params->Player->Party;

	std::sort(enemies.begin(), enemies.end(), [] (Entity* a, Entity* b) {return a->getStats().Agility > b->getStats().Agility; });
	std::sort(party.begin(), party.end(), [] (Entity* a, Entity* b) {return a->getStats().Agility > b->getStats().Agility; });

	unsigned int i = 0, j = 0;
	while (i < 4 || j < enemies.size())
	{
		// If we're done with a, just gobble up b
		if (i >= 4)
		{
			_queue.push(enemies[j++]);
			continue;
		}
		
		// If we're done with b, just gobble up a
		if (j >= enemies.size())
		{
			_queue.push(party[i++]);
			continue;
		}

		Entity* min;
		int a = (*party[i]).getStats().Agility;
		int b = (*enemies[j]).getStats().Agility;
		
		//Choose the larger of a or b
		min = a >= b ? party[i++] : enemies[j++];

		_queue.push( min );
	}
}