#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <memory>
#include "..\Entities\Player.hpp"
#include "..\Params\Params.hpp"

class StateMachine;

namespace sf
{
	class RenderWindow;
	class Time;
}

class GameState
{
public:
	GameState(StateMachine& machine, sf::RenderWindow& window, bool replace = true, std::unique_ptr<Params> = nullptr);
	virtual ~GameState();

	virtual void pause() = 0;
	virtual void resume(const std::unique_ptr<Params> = nullptr) = 0;

	virtual void update(const sf::Time) = 0;
	virtual void processEvents() = 0;
	virtual void draw() = 0;

	std::unique_ptr<GameState> next();

	bool isReplacing();

protected:
    StateMachine& _machine;
    sf::RenderWindow& _window;

	std::unique_ptr<Params> _parameters;
	bool _replacing;
	std::unique_ptr<GameState> _next;
};

#endif // GAMESTATE_HPP
