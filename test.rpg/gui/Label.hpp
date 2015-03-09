#ifndef LABEL_HPP
#define LABEL_HPP

#include <memory>
#include <vector>

#include <SFML/Graphics/Text.hpp>
#include "sfml/Graphics/RectangleShape.hpp"

#include "Widget.hpp"


namespace sf
{
	class Font;
	class RenderStates;
	class RenderTarget;
}

namespace gui
{
	class Label : public Widget
	{
	public:
		Label(const sf::Font&, const std::string&, unsigned int charSize = 30u);
		Label();

		void setText(const std::string&);
		void setColour(const sf::Color&);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		sf::Text _text;
	};

	class Bar : public Widget
	{
	public:
		Bar(sf::Vector2f& size);

		void setBar(float p);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		sf::RectangleShape _background;
		sf::RectangleShape _foreground;

	};

}

#endif