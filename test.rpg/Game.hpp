#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFGUI/SFGUI.hpp>
#include <Thor/Resources/MultiResourceCache.hpp>
#include <memory>

#include "States/StateMachine.hpp"
#include "States/IntroState.hpp"

class Game
{
public:
	Game();
	void run();
	static const sf::Vector2u Size;
	static const std::unique_ptr<thor::MultiResourceCache> Cache;
	static const std::unique_ptr<sf::Font> Font;

private:
	StateMachine _machine;
	sf::RenderWindow _window;
	static const sf::Time _timePerFrame;

};

#endif // GAME_HPP
