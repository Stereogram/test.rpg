#include "StateMachine.hpp"
#include "GameState.hpp"

#include <iostream>
#include <memory>

StateMachine::StateMachine()
: _resume(false)
, _running(false)
{
	std::cout << "StateMachine Init" << std::endl;
}

void StateMachine::run( std::unique_ptr<GameState> state )
{
	_running = true;

	_states.push(std::move(state));
}

void StateMachine::nextState()
{
    if(_resume)
    {
        // Cleanup the current state
		if (!_states.empty())
			_states.pop();
        
        // Resume previous state
        if (!_states.empty())
			_states.top()->resume(std::move(_returnParams));
        
        _resume = false;
    }

	// There needs to be a state
	if (!_states.empty())
	{
		std::unique_ptr<GameState> temp = _states.top()->next();

		// Only change states if there's a next one existing
		if(temp != nullptr)
		{
			// Replace the running state
			if(temp->isReplacing())
				_states.pop();
			// Pause the running state
			else
				_states.top()->pause();

			_states.push(std::move(temp));
		}
	}
}

void StateMachine::lastState(std::unique_ptr<Params> params)
{
	_returnParams = std::move(params);
    _resume = true;
}

void StateMachine::update(const sf::Time& dt)
{
	// Let the state update the game
	_states.top()->update(dt);
}

void StateMachine::processEvents()
{
	_states.top()->processEvents();
}

void StateMachine::draw()
{
	// Let the state draw the screen
	_states.top()->draw();
}
