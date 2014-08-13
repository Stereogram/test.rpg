#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include <memory>
#include <vector>

#include <sfml/Graphics/RectangleShape.hpp>
#include <Thor/Resources/ResourceKey.hpp>

#include "Widget.hpp"
#include "Label.hpp"

namespace sf
{
	class RenderStates;
	class RenderTarget;
}

namespace gui
{
	class TextBox : public Widget
	{
	public:
		TextBox(std::unique_ptr<std::vector<std::string>>, const unsigned int);
		TextBox(const unsigned int);
		void add(const std::string&);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		std::vector<std::unique_ptr<gui::Label>> _lines;
		unsigned int _max;
		std::shared_ptr<sf::Font> _font;
	};
}

#endif