#ifndef BOX_HPP
#define BOX_HPP

#include <memory>
#include <vector>

#include <sfml/Graphics/RectangleShape.hpp>
#include <Thor/Resources/ResourceKey.hpp>

#include "Widget.hpp"

namespace sf
{
	class Texture;
	class RenderStates;
	class RenderTarget;
}

namespace gui
{
	class Box : public Widget
	{
	public:
		Box();
		Box(const thor::ResourceKey<sf::Texture>, const sf::Vector2f&);
		Box(const sf::Color&  , const sf::Vector2f&);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		sf::RectangleShape _shape;
	};
}

#endif