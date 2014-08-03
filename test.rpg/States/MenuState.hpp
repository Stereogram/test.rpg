#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "GameState.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Text.hpp>

class StateMachine;

namespace sf
{
	class RenderWindow;
}

class MenuState : public GameState
{
public:
	MenuState(StateMachine& machine, sf::RenderWindow& window, bool replace = true, std::unique_ptr<Params> = nullptr);

	void pause();
	void resume(std::unique_ptr<Params> = nullptr);

	void update(const sf::Time&);
	void processEvents();
	void draw();

private:
	sf::Text _state;
	std::unique_ptr<Params> _params;
	sf::RectangleShape _background;
	std::vector<sf::Text> _menuItems;
	size_t _selected;
};

#endif // MENUSTATE_HPP
