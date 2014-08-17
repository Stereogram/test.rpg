#include <memory>

#include <Thor\Resources\SfmlLoaders.hpp>

#include "Game.hpp"

const sf::Time Game::_timePerFrame = sf::seconds(1.0f / 60.0f);
const sf::Vector2u Game::Size = sf::Vector2u(720, 480);
const std::unique_ptr<thor::MultiResourceCache> Game::Cache(new thor::MultiResourceCache);
const std::unique_ptr<sf::Font> Game::Font(new sf::Font);

Game::Game()
{
	_window.setVerticalSyncEnabled(true);
	_window.create( sf::VideoMode{Size.x, Size.y}, "Engine Test v2.1", sf::Style::None );


	std::unique_ptr<Params> test = std::unique_ptr<Params>(new Params("init"));
	test->Player = std::unique_ptr<Player>(new Player());
	for (unsigned int i = 0; i < 4; i++)
	{
		Entity* t = new Entity(thor::Resources::fromFile<sf::Texture>("assets/soldier.png"), sf::Vector2u(32, 32), Animation::readAnimation("assets/soldier.ani"));
		t->getStats().Agility = i + 10;
		test->Player->Party->push_back(t);
	}
	_machine.run(StateMachine::build<IntroState>(_machine, _window, true, std::move(test)));



	Font->loadFromFile("assets/fonts/kenpixel_high_square.ttf");
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
