#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <memory>

class StateMachine;

namespace sf
{
	class RenderWindow;
	class Time;
}

class GameState
{
public:
	GameState( StateMachine& machine, sf::RenderWindow& window, bool replace = true );
	virtual ~GameState();

	virtual void pause() = 0;
	virtual void resume() = 0;

	virtual void update(sf::Time) = 0;
	virtual void processEvents() = 0;
	virtual void draw() = 0;

	std::unique_ptr<GameState> next();

	bool isReplacing();

protected:
    StateMachine& _machine;
    sf::RenderWindow& _window;

	bool _replacing;

	std::unique_ptr<GameState> _next;
};

#endif // GAMESTATE_HPP
