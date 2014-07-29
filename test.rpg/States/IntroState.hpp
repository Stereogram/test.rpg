#ifndef INTROSTATE_HPP
#define INTROSTATE_HPP

#include "GameState.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class StateMachine;

namespace sf
{
	class RenderWindow;
}

class IntroState : public GameState
{
public:
	IntroState( StateMachine& game, sf::RenderWindow& window, bool replace = true );

	void pause();
	void resume();

	void update(sf::Time);
	void processEvents();
	void draw();

private:

};

#endif // INTROSTATE_HPP
