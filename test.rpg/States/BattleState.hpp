#ifndef BATTLESTATE_HPP
#define BATTLESTATE_HPP

#include "GameState.hpp"
#include "..\gui\Box.hpp"
#include "..\gui\TextBox.hpp"

namespace sf
{
	class RenderWindow;
	class Text;
}

class StateMachine;

class BattleState : public GameState
{
public:
	BattleState(StateMachine& game, sf::RenderWindow& window, bool replace = true, std::unique_ptr<Params> = nullptr);

	void pause();
	void resume(std::unique_ptr<Params> = nullptr);

	void update(const sf::Time&);
	void processEvents();
	void draw() const;

private:
	sf::Text _state;

	gui::Box _healthBox;
	gui::Box _background;
	gui::TextBox _messages;

};

#endif // BATTLESTATE_HPP