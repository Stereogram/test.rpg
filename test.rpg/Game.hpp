#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <memory>

#include "StateMachine.hpp"
#include "IntroState.hpp"

class Game
{
public:
	Game();
	void run();
	static const sf::Vector2u Size;
	static const std::unique_ptr<sf::Font> Font;

private:
	StateMachine _machine;
	sf::RenderWindow _window;
	static const sf::Time _timePerFrame;

};

#endif // GAME_HPP
