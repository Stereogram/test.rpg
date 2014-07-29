#ifndef INTROSTATE_HPP
#define INTROSTATE_HPP

#include "GameState.hpp"

#include "SFML/Graphics/Text.hpp"

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
	sf::Text _state;
};

#endif // INTROSTATE_HPP
