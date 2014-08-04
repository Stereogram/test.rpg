#include <memory>
#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Event.hpp>

#include "StateMachine.hpp"
#include "MenuState.hpp"
#include "../Game.hpp"

MenuState::MenuState(StateMachine& machine, sf::RenderWindow& window, bool replace, std::unique_ptr<Params> params)
: GameState(machine, window, replace, std::move(params))
, _menu(std::unique_ptr<gui::Box>(new gui::Box()), std::vector<std::string>() )
{
	_state = sf::Text("MenuState", *Game::Font);
	
	std::cout << "MenuState Init params:" << _params->State << std::endl;
	_params->State = "MenuState";

	_window.setView(_window.getDefaultView());

	for (int i = 0; i < 5; i++)
	{
		_menu.add("herp " + std::to_string(i));
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
						_menu.prev();
						break;
					case sf::Keyboard::Down:
						_menu.next();
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

void MenuState::draw() const
{
	// Clear the previous drawing
	_window.clear();
	_window.draw(_menu);
	_window.draw(_state);
	_window.display();
}