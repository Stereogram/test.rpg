#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "GameState.hpp"
#include <SFML\Graphics\Text.hpp>
#include "..\Util\AnimatedSprite.hpp"

class StateMachine;

namespace sf
{
	class RenderWindow;
}

class PlayState : public GameState
{
public:
	PlayState( StateMachine& machine, sf::RenderWindow& window, bool replace = true );

	void pause();
	void resume();

	void update(sf::Time);
	void processEvents();
	void draw();

private:
	sf::Text _state;
	AnimatedSprite _sprite;
};

#endif // PLAYSTATE_HPP
