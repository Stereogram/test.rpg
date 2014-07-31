#ifndef BATTLESTATE_HPP
#define BATTLESTATE_HPP

#include "GameState.hpp"

#include "SFML/Graphics/Text.hpp"

class StateMachine;

namespace sf
{
	class RenderWindow;
}

class BattleState : public GameState
{
public:
	BattleState(StateMachine& game, sf::RenderWindow& window, bool replace = true);

	void pause();
	void resume();

	void update(const sf::Time);
	void processEvents();
	void draw();

private:
	sf::Text _state;
};

#endif // BATTLESTATE_HPP