#include <memory>
#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Event.hpp>

#include "StateMachine.hpp"
#include "MenuState.hpp"
#include "../Game.hpp"

MenuState::MenuState(StateMachine& machine, sf::RenderWindow& window, bool replace, std::unique_ptr<Params> params)
: GameState(machine, window, replace)
, _params(std::move(params))
, _background(static_cast<sf::Vector2f>(Game::Size))
, _menuItems()
, _selected(0)
{
	_state = sf::Text("MenuState", *Game::Font);
	
	std::cout << "MenuState Init params:" << _params->State << std::endl;
	_params->State = "MenuState";

	_window.setView(_window.getDefaultView());


	_menuItems.push_back(sf::Text("herp 1", *Game::Font, 30));
	_menuItems.push_back(sf::Text("herp 2", *Game::Font, 30));
	_menuItems.push_back(sf::Text("herp 3", *Game::Font, 30));
	_menuItems.push_back(sf::Text("herp 4", *Game::Font, 30));
	_menuItems.push_back(sf::Text("herp 5", *Game::Font, 30));

	for (size_t i = 0; i < _menuItems.size(); i++)
	{
		_menuItems[i].setColor(sf::Color::Blue);
		_menuItems[i].setPosition(Game::Size.x-200.0f, (30.0f*i) +20 );
	}
}

void MenuState::pause()
{
	std::cout << "MenuState Pause" << std::endl;
}

void MenuState::resume(std::unique_ptr<Params> params)
{
	std::cout << "MenuState Resume from " << params->State << std::endl;
}

void MenuState::update(const sf::Time& dt)
{
	sf::Event event;
	_menuItems[_selected].setColor(sf::Color::Blue);
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
					case sf::Keyboard::Up:
						_selected = _selected == 0 ? _menuItems.size() - 1 : _selected - 1;
						break;
					case sf::Keyboard::Down:
						_selected = _selected + 1 >= _menuItems.size() ? 0 : _selected + 1;
						break;
					default:
						break;
				}
				break;

			default:
				break;
		}

		

	}
	_menuItems[_selected].setColor(sf::Color::Cyan);
}

void MenuState::processEvents()
{

}

void MenuState::draw()
{
	// Clear the previous drawing
	_window.clear();
	_window.draw(_background);
	_window.draw(_state);
	for (sf::Text t : _menuItems)
	{
		_window.draw(t);
	}
	_window.display();
}