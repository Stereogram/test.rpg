#include <Thor\Resources\SfmlLoaders.hpp>
#include "SFML\Graphics\Font.hpp"

#include "TextBox.hpp"
#include "Label.hpp"
#include "..\Game.hpp"

gui::TextBox::TextBox(const unsigned int maxLines)
: _font(Game::Cache->acquire(thor::Resources::fromFile<sf::Font>("assets/fonts/kenpixel_high_square.ttf")))
, _max(maxLines)
{
	_animator.addAnimation("move", [] (Label& label, float progress) {label.move(0.f, progress * -2.f); }, sf::seconds(0.5f));
}

void gui::TextBox::add(const std::string& item)
{
	_animator.playAnimation("move");
	if (_lines.size() >= _max)
		_lines.pop_front();
	_lines.push_back(std::unique_ptr<Label>(new Label(*_font, item)));
}

void gui::TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	for (const auto& item : _lines)
	{
		item->draw(target, states);
	}
	for (const auto& child : _children)
	{
		child->draw(target, states);
	}
}

void gui::TextBox::update(const sf::Time& dt)
{
	_animator.update(dt);
	for (const auto& label : _lines)
	{
		_animator.animate(*label);
	}
}

