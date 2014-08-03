#ifndef BATTLESTATE_HPP
#define BATTLESTATE_HPP

#include "GameState.hpp"

#include "SFML/Graphics/Text.hpp"
#include "../Entities/Player.hpp"

class StateMachine;

namespace sf
{
	class RenderWindow;
}

class BattleState : public GameState
{
public:
	BattleState(StateMachine& game, sf::RenderWindow& window, bool replace = true, std::unique_ptr<Params> = nullptr);

	void pause();
	void resume(std::unique_ptr<Params> = nullptr);

	void update(const sf::Time&);
	void processEvents();
	void draw();

private:
	sf::Text _state;
	std::unique_ptr<Params> _params;
};

#endif // BATTLESTATE_HPP