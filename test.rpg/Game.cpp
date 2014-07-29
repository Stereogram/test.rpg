#include "Game.hpp"

const sf::Time Game::_timePerFrame = sf::seconds(1.0f / 60.0f);
const sf::Vector2u Game::Size = sf::Vector2u(720, 480);
const std::unique_ptr<sf::Font> Game::Font(new sf::Font);

Game::Game()
{
	Font->loadFromFile("C:\\Windows\\Fonts\\arial.ttf");
	_window.setVerticalSyncEnabled(true);
	// Create render window
	_window.create( sf::VideoMode{Size.x, Size.y}, "Engine Test v2.1", sf::Style::None );

	// Initialize the engine
	_machine.run( StateMachine::build<IntroState>( _machine, _window, true ) );
}

void Game::run()
{
	sf::Clock timer;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	
	while (_machine.running())
	{
		_machine.nextState();
		_machine.processEvents();
		sf::Time dt = timer.getElapsedTime();
		timer.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > _timePerFrame)
		{
			timeSinceLastUpdate -= _timePerFrame;
			_machine.processEvents();
			_machine.update(_timePerFrame);
		}
		_machine.draw();
	}
}
