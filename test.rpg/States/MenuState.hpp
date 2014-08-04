#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "GameState.hpp"

namespace sf
{
	class RenderWindow;
	class Text;
	class Texture;
}

class StateMachine;

class MenuState : public GameState
{
public:
	MenuState(StateMachine& machine, sf::RenderWindow& window, bool replace = true, std::unique_ptr<Params> = nullptr);

	void pause();
	void resume(std::unique_ptr<Params> = nullptr);

	void update(const sf::Time&);
	void processEvents();
	void draw() const;

private:
	sf::Text _state;
	sf::RectangleShape _background;
	std::vector<sf::Text> _menuItems;
	size_t _selected;
};

#endif // MENUSTATE_HPP
