#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include <memory>
#include <deque>

#include <sfml/Graphics/RectangleShape.hpp>
#include <Thor/Resources/ResourceKey.hpp>
#include <Thor/Animation/Animator.hpp>
#include "SFML/System/Time.hpp"

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
		TextBox(const unsigned int);
		void add(const std::string&);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void update(const sf::Time&);

	private:
		thor::Animator<gui::Label, std::string> _animator;
		std::deque<std::unique_ptr<gui::Label>> _lines;
		unsigned int _max;
		std::shared_ptr<sf::Font> _font;
	};
}

#endif