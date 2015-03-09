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
, _messages(4)
, _healthBox(sf::Color::Magenta, sf::Vector2f(static_cast<float>(Game::Size.x), Game::Size.y / 5.f))
, _current(0)
, _timer(sf::Time::Zero)
, _testBox(sf::Color::Black, sf::Vector2f(Game::Size.x, Game::Size.y - 100.f))
{
	_state = sf::Text("BattleState", *Game::Font);
	
	std::cout << "BattleState Init params:" << _params->State << std::endl;
	_params->State = "BattleState";

	_window.setView(_window.getDefaultView());

	_messages.setPosition(20.f, Game::Size.y);
	_messages.add("testest");

	merge();
	

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

	//todo: convert to callbacks, eventloop is lame.
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
				 case sf::Keyboard::N:
					 _params->Player->Party[0]->getStats().Agility += 10;
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
	
	if ((_timer += dt) >= sf::seconds(2))
	{
		_messages.add(_queue[_current]->Name + " | " + std::to_string(_queue[_current]->getStats().Agility));
		_current = _current + 1 >= _queue.size() ? 0 : _current + 1;
		_timer = sf::Time::Zero;
	}

	_messages.update(dt);
}

void BattleState::processEvents()
{

}

void BattleState::draw() const
{
	// Clear the previous drawing
	_window.clear();
	_window.draw(_background);
	_window.draw(_messages);
	_window.draw(_testBox);
	_window.draw(_healthBox);
	_window.draw(_state);
	_window.display();
}

void BattleState::merge()
{
	auto enemies = dynamic_cast<BattleParams*>(_params.get())->Enemies;
	auto party = _params->Player->Party;

	std::sort(enemies.begin(), enemies.end(), [] (std::shared_ptr<Entity> a, std::shared_ptr<Entity> b) {return a->getStats().Agility > b->getStats().Agility; });
	std::sort(party.begin(), party.end(), [] (std::shared_ptr<Entity> a, std::shared_ptr<Entity> b) {return a->getStats().Agility > b->getStats().Agility; });

	unsigned int i = 0, j = 0;
	while (i < 4 || j < enemies.size())
	{
		// If we're done with a, just gobble up b
		if (i >= 4)
		{
			_queue.push_back(enemies[j++]);
			continue;
		}

		// If we're done with b, just gobble up a
		if (j >= enemies.size())
		{
			_queue.push_back(party[i++]);
			continue;
		}


		int a = party[i]->getStats().Agility;
		int b = enemies[j]->getStats().Agility;

		//Choose the larger of a or b
		auto min = a >= b ? party[i++] : enemies[j++];

		_queue.push_back(min);
	}
}