
#include "Box.hpp"
#include "..\Game.hpp"
#include <memory>

gui::Box::Box(const thor::ResourceKey<sf::Texture> textureKey, const sf::Vector2f& size)
: _shape(size)
, _vertical(true)
, _outline(0)
{
	_shape.setTexture(Game::Cache->acquire(textureKey).get());
}

gui::Box::Box(const sf::Color& colour, const sf::Vector2f& size)
: _shape(size)
, _vertical(true)
, _outline(0)
{
	_shape.setFillColor(colour);
}

gui::Box::Box()
: _shape(static_cast<sf::Vector2f>(Game::Size))
, _vertical(true)
, _outline(0)
{
	_shape.setFillColor(sf::Color::Blue);
}

void gui::Box::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_shape, states);
	for (const auto& child : _children)
	{
		child->draw(target, states);
	}
}

