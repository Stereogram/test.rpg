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
, _testBox(sf::Color::Black, sf::Vector2f(static_cast<float>(Game::Size.x), Game::Size.y - 100.f))
{
	_state = sf::Text("BattleState", *Game::Font);
	
	std::cout << "BattleState Init params:" << _params->State << std::endl;
	_params->State = "BattleState";

	_window.setView(_window.getDefaultView());

	_messages.setPosition(20.f, static_cast<float>(Game::Size.y));
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
				 case sf::Keyboard::A:
					 _params->Player->Party[0]->getStats().Health.increase(10);
					 break;
				 case sf::Keyboard::S:
					 _params->Player->Party[0]->getStats().Health.decrease(20);
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
	
	for (const auto& member : _params->Player->Party)
	{
		member->getHealthBar().setBar(member->getStats().Health.getPercent());
		member->getManaBar().setBar(member->getStats().Mana.getPercent());
		member->getHealthLabel().setText(Stat::to_string(member->getStats().Health));
		member->getManaLabel().setText(Stat::to_string(member->getStats().Mana));
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
	if (_params == nullptr)
		return;
	// Clear the previous drawing
	_window.clear();
	_window.draw(_background);
	_window.draw(_messages);
	_window.draw(_testBox);
	_window.draw(_healthBox);
	for (const auto& member : _params->Player->Party)
	{
		_window.draw(member->getHealthBar());
		_window.draw(member->getManaBar());
		_window.draw(member->getHealthLabel());
		_window.draw(member->getManaLabel());
	}

	_window.draw(_state);
	_window.display();
}

void BattleState::merge()
{
	auto enemies = dynamic_cast<BattleParams*>(_params.get())->Enemies;
	auto party = _params->Player->Party;

	std::sort(enemies.begin(), enemies.end(), [] (std::shared_ptr<Entity> a, std::shared_ptr<Entity> b) {return a->getStats().Agility > b->getStats().Agility; });
	std::sort(party.begin(), party.end(), [] (std::shared_ptr<Entity> a, std::shared_ptr<Entity> b) {return a->getStats().Agility > b->getStats().Agility; });

	separatePartyGUI();

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

void BattleState::separatePartyGUI()
{
	for (unsigned int i = 0; i < _params->Player->Party.size(); i++)
	{
		_params->Player->Party[i]->getHealthBar().setPosition(100.f + (i * 75.f), 20.f);
		_params->Player->Party[i]->getManaBar().setPosition(100.f + (i * 75.f), 35.f);

		_params->Player->Party[i]->getHealthLabel().setPosition(110.f + (i * 75.f), 17.f);
		_params->Player->Party[i]->getManaLabel().setPosition(110.f + (i * 75.f), 32.f);
	}
}