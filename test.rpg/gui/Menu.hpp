#ifndef MENU_HPP
#define MENU_HPP

#include <memory>
#include <vector>

#include <sfml/Graphics/RectangleShape.hpp>
#include <Thor/Resources/ResourceKey.hpp>

#include "Widget.hpp"
#include "Box.hpp"
#include "Label.hpp"

namespace sf
{
	class RenderStates;
	class RenderTarget;
}

namespace gui
{
	class Menu : public Widget
	{
	public:
		Menu(std::unique_ptr<Box>, std::vector<std::string>&);

		void add(const std::string&);
		void remove(const unsigned int index);
		void next();
		void prev();
		unsigned int getIndex() { return _selected; }

		std::unique_ptr<gui::Label> operator[](int index);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		std::unique_ptr<gui::Box> _box;
		std::vector<std::unique_ptr<gui::Label>> _menuItems;
		unsigned int _selected;
		std::shared_ptr<sf::Font> _font;
	};
}

#endif