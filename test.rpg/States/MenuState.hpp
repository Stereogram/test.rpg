#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "GameState.hpp"
#include "..\gui\Menu.hpp"
#include "..\gui\Box.hpp"

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
	void test();
	sf::Text _state;
	std::shared_ptr<gui::Menu> _current;
	std::stack<gui::Box*> _menus;
};

#endif // MENUSTATE_HPP
