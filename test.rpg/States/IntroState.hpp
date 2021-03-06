#ifndef INTROSTATE_HPP
#define INTROSTATE_HPP

#include "GameState.hpp"

namespace sf
{
	class RenderWindow;
	class Text;
}

class StateMachine;

class IntroState : public GameState
{
public:
	IntroState(StateMachine& game, sf::RenderWindow& window, bool replace = true, std::unique_ptr<Params> = nullptr);

	void pause();
	void resume(std::unique_ptr<Params> = nullptr);

	void update(const sf::Time&);
	void processEvents();
	void draw() const;

private:
	sf::Text _state;
};

#endif // INTROSTATE_HPP
