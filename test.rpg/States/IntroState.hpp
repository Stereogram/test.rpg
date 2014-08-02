#ifndef INTROSTATE_HPP
#define INTROSTATE_HPP

#include "GameState.hpp"

#include "SFML/Graphics/Text.hpp"
#include "../Entities/Player.hpp"

class StateMachine;

namespace sf
{
	class RenderWindow;
}

class IntroState : public GameState
{
public:
	IntroState(StateMachine& game, sf::RenderWindow& window, bool replace = true, std::unique_ptr<Params> = nullptr);

	void pause();
	void resume(const std::unique_ptr<Params> = nullptr);

	void update(const sf::Time);
	void processEvents();
	void draw();

private:
	sf::Text _state;
};

#endif // INTROSTATE_HPP
