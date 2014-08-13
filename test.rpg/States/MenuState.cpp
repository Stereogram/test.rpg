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
, _current(new gui::Menu())
, _menus()
{
	_state = sf::Text("MenuState", *Game::Font);
	
	std::cout << "MenuState Init params:" << _params->State << std::endl;
	_params->State = "MenuState";

	_window.setView(_window.getDefaultView());

	for (int i = 0; i < 5; i++)
	{
		_current->add("herp " + std::to_string(i));
	}
	_current->setPosition(200.f, 200.f);//todo: fix this
	gui::Box* temp = new gui::Box();
	temp->attach(_current);
	_menus.push(temp);
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
						_current->prev();
						break;
					case sf::Keyboard::Down:
						_current->next();
						break;
					case sf::Keyboard::A:
						test();
						break;
					case sf::Keyboard::S:
						_menus.pop();
						_current = std::dynamic_pointer_cast<gui::Menu>(_menus.top()->getChild(0));
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
	_window.draw(*_menus.top());
	_window.draw(_state);
	_window.display();
}

void MenuState::test()
{
	_current = std::shared_ptr<gui::Menu>(new gui::Menu());
	for (int i = 0; i < 10; i++)
	{
		_current->add("derp " + std::to_string(i));
	}
	_current->setPosition(20.f, 20.f);
	gui::Box* temp = new gui::Box();
	temp->attach(_current);
	_menus.push(temp);

}
