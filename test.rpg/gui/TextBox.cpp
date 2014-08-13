#include <Thor\Resources\SfmlLoaders.hpp>
#include "SFML\Graphics\Font.hpp"

#include "TextBox.h"
#include "Label.hpp"
#include "..\Game.hpp"

gui::TextBox::TextBox(std::unique_ptr<std::vector<std::string>> lines, const unsigned int maxLines)
: _font(Game::Cache->acquire(thor::Resources::fromFile<sf::Font>("assets/fonts/kenpixel_high_square.ttf")))
, _max(maxLines)
{
	for (size_t i = 0; i < lines->size(); i++)
	{
		add( (*lines)[i]);
	}
}

gui::TextBox::TextBox(const unsigned int maxLines)
: _max(maxLines)
{
}

void gui::TextBox::add(const std::string& item)
{
	auto t = std::unique_ptr<gui::Label>(new Label(*_font, item));
	t->setPosition(0.f, (30.f*_lines.size()));//hardcoded positions ftw.
	_lines.push_back(std::move(t));
}

void gui::TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states = getTransform();
	for (const auto& item : _lines)
	{
		item->draw(target, states);
	}
	for (const auto& child : _children)
	{
		child->draw(target, states);
	}
}

