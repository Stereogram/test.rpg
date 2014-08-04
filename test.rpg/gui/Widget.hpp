#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <memory>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <sfml/Graphics/Transformable.hpp>

namespace gui
{
	class Widget : public sf::Drawable, public sf::Transformable
	{
	public:
		Widget(): _children(), _visible(true){ }
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
		virtual void attach(std::unique_ptr<Widget> child) { _children.push_back(std::move(child)); }
		virtual void visible(const bool b) { _visible = b; }

	protected:
		std::vector<std::unique_ptr<Widget>> _children;
		bool _visible;

	private:
		Widget(Widget const&);
		void operator=(Widget const&);
	};
}

#endif