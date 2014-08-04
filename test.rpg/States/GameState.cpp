#include "GameState.hpp"

GameState::GameState(StateMachine& machine, sf::RenderWindow& window, bool replace, std::unique_ptr<Params> params)
: _machine(machine)
, _window(window)
, _replacing(replace)
, _params(std::move(params))
{

}

GameState::~GameState()
{

}

std::unique_ptr<GameState> GameState::next()
{
	return std::move(_next);
}

bool GameState::isReplacing()
{
	return _replacing;
}