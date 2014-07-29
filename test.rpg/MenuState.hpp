#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "GameState.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class StateMachine;

namespace sf
{
	class RenderWindow;
}

class MenuState : public GameState
{
public:
	MenuState( StateMachine& machine, sf::RenderWindow& window, bool replace = true );

	void pause();
	void resume();

	void update(sf::Time);
	void processEvents();
	void draw();

private:

};

#endif // MENUSTATE_HPP
