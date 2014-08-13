#include <SFML\Graphics\RenderTarget.hpp>

#include "Label.hpp"

gui::Label::Label(const sf::Font& font, const std::string& text, unsigned int charSize)
: _text(text, font, charSize)
{
}

void gui::Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(_text, states);
	for (const auto& child : _children)
	{
		child->draw(target, states);
	}
}

void gui::Label::setText(const std::string& text)
{
	_text.setString(text);
}

void gui::Label::setColour(const sf::Color& colour)
{
	_text.setColor(colour);
}
