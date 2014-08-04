#ifndef LABEL_HPP
#define LABEL_HPP

#include <memory>
#include <vector>

#include <SFML/Graphics/Text.hpp>

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

		void setText(const std::string&);
		void setColour(const sf::Color&);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		sf::Text _text;
	};
}

#endif