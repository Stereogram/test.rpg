#ifndef BATTLESTATE_HPP
#define BATTLESTATE_HPP

#include "GameState.hpp"
#include "..\gui\Box.hpp"
#include "..\gui\TextBox.hpp"
#include <vector>

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
	void merge();

	sf::Text _state;

	gui::Box _healthBox;
	gui::Box _background;
	gui::Box _testBox;
	gui::TextBox _messages;

	std::vector<std::shared_ptr<Entity>> _queue;
	unsigned int _current;
	sf::Time _timer;

};

#endif // BATTLESTATE_HPP