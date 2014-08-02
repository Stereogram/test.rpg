#include <memory>
#include <iostream>

#include "StateMachine.hpp"
#include "PlayState.hpp"
#include "MenuState.hpp"
#include "../Game.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <Thor/Resources/ResourceKey.hpp>
#include "BattleState.hpp"

PlayState::PlayState(StateMachine& machine, sf::RenderWindow& window, bool replace, std::unique_ptr<Params> params)
: GameState( machine, window, replace )
, _sprite(thor::Resources::fromFile<sf::Texture>("assets/soldier.png"), sf::Vector2u(32,32), Animation::readAnimation("assets\\soldier.ani"))
, _params(new Params("PlayState"))
{
	_state = sf::Text("PlayState", *Game::Font);
	std::cout << "PlayState Init " << _params->State << std::endl;
	sf::View v = _window.getDefaultView();
	v.zoom(.5f);
	v.setCenter(100, 100);
	_window.setView(v);
}

void PlayState::pause()
{
	std::cout << "PlayState Pause" << std::endl;
}

void PlayState::resume(const std::unique_ptr<Params> params)
{
	std::cout << "PlayState Resume from " << params->State << std::endl;
}

void PlayState::update(const sf::Time dt)
{
	_sprite.update(dt);
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
						_next = StateMachine::build<MenuState>(_machine, _window, false, std::move(_params));
						break;
					case sf::Keyboard::B:
						_next = StateMachine::build<BattleState>(_machine, _window, false, std::move(_params));
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
	_window.draw(_state);
	_window.draw(_sprite);
	_window.display();
}