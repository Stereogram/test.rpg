#include <SFML\Graphics\RenderTarget.hpp>

#include "Label.hpp"
#include "..\Game.hpp"

gui::Label::Label(const sf::Font& font, const std::string& text, unsigned int charSize)
: _text(text, font, charSize)
{
}

gui::Label::Label()
: _text("", *Game::Font)
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

gui::Bar::Bar(sf::Vector2f& size)
: _background(size)
, _foreground(size)
{
	_background.setFillColor(sf::Color::Red);
	_foreground.setFillColor(sf::Color::Blue);
}

void gui::Bar::setBar(float p)
{

	_foreground.setScale(p, 1.f);
}

void gui::Bar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(_background, states);
	target.draw(_foreground, states);
	for (const auto& child : _children)
	{
		child->draw(target, states);
	}
}