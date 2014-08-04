#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "GameState.hpp"

namespace sf
{
	class RenderWindow;
	class Text;
}

class StateMachine;
class AnimatedSprite;

class PlayState : public GameState
{
public:
	PlayState(StateMachine& machine, sf::RenderWindow& window, bool replace = true, std::unique_ptr<Params> = nullptr);

	void pause();
	void resume(std::unique_ptr<Params> = nullptr);

	void update(const sf::Time&);
	void processEvents();
	void draw() const;


private:
	sf::Text _state;
	AnimatedSprite _sprite;
	std::shared_ptr<sf::Font> _font;
};

#endif // PLAYSTATE_HPP
