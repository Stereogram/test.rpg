#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "GameState.hpp"
#include <SFML\Graphics\Text.hpp>
#include "..\Util\AnimatedSprite.hpp"
#include "..\Entities\Player.hpp"

class StateMachine;

namespace sf
{
	class RenderWindow;
}

class PlayState : public GameState
{
public:
	PlayState(StateMachine& machine, sf::RenderWindow& window, bool replace = true, std::unique_ptr<Params> = nullptr);

	void pause();
	void resume(std::unique_ptr<Params> = nullptr);

	void update(const sf::Time&);
	void processEvents();
	void draw();


private:
	sf::Text _state;
	AnimatedSprite _sprite;
	std::unique_ptr<Params> _params;
};

#endif // PLAYSTATE_HPP
