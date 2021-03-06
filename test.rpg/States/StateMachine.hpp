#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include <memory>
#include <stack>
#include <string>
#include "SFML\System\Time.hpp"
#include "..\Entities\Player.hpp"
#include "..\Params\Params.hpp"

class GameState;

namespace sf
{
	class RenderWindow;
}

class StateMachine
{
public:
	StateMachine();

	void run(std::unique_ptr<GameState> state);

	void nextState();
	void lastState(std::unique_ptr<Params> = nullptr);

	void update(const sf::Time&);
	void processEvents();
	void draw();

	bool running() { return _running; }
	void quit() { _running = false; }

	template <typename T>
	static std::unique_ptr<T> build(StateMachine& machine, sf::RenderWindow& window, bool replace = true, std::unique_ptr<Params> = nullptr);

private:
	// The stack of states
	std::stack<std::unique_ptr<GameState>> _states;
	std::unique_ptr<Params> _returnParams;
	bool _resume;
	bool _running;
};

template <typename T>
std::unique_ptr<T> StateMachine::build(StateMachine& machine, sf::RenderWindow& window, bool replace, std::unique_ptr<Params> params)
{
	return std::move( std::unique_ptr<T>(new T( machine, window, replace, std::move(params) )));
}

#endif // GAMEENGINE_HPP
