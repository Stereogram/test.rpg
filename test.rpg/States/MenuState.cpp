#include <memory>
#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Event.hpp>

#include "StateMachine.hpp"
#include "MenuState.hpp"
#include "../Game.hpp"
#include "../gui/Widget.hpp"

MenuState::MenuState(StateMachine& machine, sf::RenderWindow& window, bool replace, std::unique_ptr<Params> params)
: GameState(machine, window, replace, std::move(params))
, _current(new gui::Menu())
, _menus()
, _text(3)
, _label()
{
	_state = sf::Text("MenuState", *Game::Font);
	
	std::cout << "MenuState Init params:" << _params->State << std::endl;
	_params->State = "MenuState";

	_window.setView(_window.getDefaultView());

	for (const auto& member : _params->Player->Party)
	{
		_current->add(member->Name);
	}
	_current->setPosition(10.f, 20.f);
	gui::Box* temp = new gui::Box();
	temp->attach(_current);
	_menus.push(temp);

	_label.setPosition(100.f, 20.f);
	_label.setText(std::to_string(_params->Player->Party[_current->getIndex()]->getStats().Agility));

	_text.setPosition(100.f, 100.f);
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
						_label.setText(std::to_string(_params->Player->Party[_current->getIndex()]->getStats().Agility));
						break;
					case sf::Keyboard::Down:
						_current->next();
						_label.setText(std::to_string(_params->Player->Party[_current->getIndex()]->getStats().Agility));
						break;
					case sf::Keyboard::A:
						test();
						break;
					case sf::Keyboard::S:
						_menus.pop();
						//point to the correct next menu. getChild(0) should be the menu.
						_current = std::dynamic_pointer_cast<gui::Menu>(_menus.top()->getChild(0));
						break;
					case sf::Keyboard::Q:
						_text.add("derp");
						break;
					default:
						break;
				}
				break;

			default:
				break;
		}

	}
	_text.update(dt);
}

void MenuState::processEvents()
{

}

void MenuState::draw() const
{
	// Clear the previous drawing
	_window.clear();
	_window.draw(*_menus.top());
	_window.draw(_label);
	_window.draw(_text);
	_window.draw(_state);
	_window.display();
}

void MenuState::test()
{
	_current = std::shared_ptr<gui::Menu>(new gui::Menu());
	for (const auto& member : _params->Player->Party)
	{
		_current->add(member->Name);
	}
	_current->setPosition(20.f, 20.f);
	gui::Box* temp = new gui::Box();
	temp->attach(_current);
	_menus.push(temp);

}
