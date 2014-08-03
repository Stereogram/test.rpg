#include "IntroState.hpp"
#include "PlayState.hpp"
#include "StateMachine.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "../Game.hpp"

#include <iostream>
#include <memory>

IntroState::IntroState(StateMachine& machine, sf::RenderWindow& window, bool replace, std::unique_ptr<Params> params)
: GameState( machine, window, replace )
, _params(std::move(params))
{
	_state = sf::Text("IntroState", *Game::Font);
	
	std::cout << "IntroState Init params:" << _params->State << std::endl;
	_params->State = "IntroState";

}

void IntroState::pause()
{
	std::cout << "IntroState Pause" << std::endl;
}

void IntroState::resume(std::unique_ptr<Params> params)
{
	std::cout << "IntroState Resume" << std::endl;
}

void IntroState::update(const sf::Time& dt)
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
            {
                switch( event.key.code )
                {
                    case sf::Keyboard::Space:
                        _next = StateMachine::build<PlayState>( _machine, _window, true, std::move(_params) );
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

void IntroState::processEvents()
{

}

void IntroState::draw()
{
	// Clear the previous drawing
	_window.clear();
	_window.draw(_state);
	_window.display();
}