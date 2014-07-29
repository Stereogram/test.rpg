#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "GameState.hpp"

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

};

#endif // PLAYSTATE_HPP
