#include <memory>
#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <Thor/Resources/ResourceKey.hpp>
#include <Thor/Resources/SfmlLoaders.hpp>

#include "../Game.hpp"
#include "../Util/Animation.hpp"
#include "StateMachine.hpp"
#include "PlayState.hpp"
#include "MenuState.hpp"
#include "BattleState.hpp"


PlayState::PlayState(StateMachine& machine, sf::RenderWindow& window, bool replace, std::unique_ptr<Params> params)
: GameState( machine, window, replace, std::move(params) )
, _sprite(thor::Resources::fromFile<sf::Texture>("assets/soldier.png"), sf::Vector2u(32,32), Animation::readAnimation("assets/soldier.ani"))
, _font(Game::Cache->acquire(thor::Resources::fromFile<sf::Font>("assets/fonts/kenpixel_high_square.ttf")))
{
	_state = sf::Text("PlayState", *_font);
	
	std::cout << "PlayState Init params:" << _params->State << std::endl;
	_params->State = "PlayState";

	sf::View v = _window.getDefaultView();
	v.zoom(.5f);
	v.setCenter(100, 100);
	_window.setView(v);

	
	std::vector<std::shared_ptr<Entity>> enemies;
	for (unsigned int i = 0; i < 4; i++)
	{
		auto t = std::shared_ptr<Entity>(new Entity(thor::Resources::fromFile<sf::Texture>("assets/soldier.png"), sf::Vector2u(32, 32), Animation::readAnimation("assets/soldier.ani")));
		t->getStats().Agility = i + 10;
		t->Name = "enemy" + std::to_string(i);
		enemies.push_back(std::move(t));
	}
	auto temp = std::unique_ptr<Params>(new BattleParams("init", enemies));
	temp->Player = std::move(_params->Player);
	_params = std::move(temp);

}

void PlayState::pause()
{
	std::cout << "PlayState Pause" << std::endl;
}

void PlayState::resume(std::unique_ptr<Params> params)
{
	_params = std::move(params);
	std::cout << "PlayState Resume from " << _params->State << std::endl;
	_params->State = "PlayState";

	sf::View v = _window.getDefaultView();
	v.zoom(.5f);
	v.setCenter(100, 100);
	_window.setView(v);

}

void PlayState::update(const sf::Time& dt)
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
					case sf::Keyboard::N:
						_params->Player->Party[0]->getStats().Agility += 2;
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


void PlayState::draw() const
{
	// Clear the previous drawing
	_window.clear();
	_window.draw(_state);
	_window.draw(_sprite);
	_window.display();
}