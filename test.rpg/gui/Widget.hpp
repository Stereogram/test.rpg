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
		virtual void attach(std::shared_ptr<Widget> child) { _children.push_back(std::move(child)); }
		void visible(const bool b) { _visible = b; }
		void setName(const std::string& name) { _name = name; }
		std::shared_ptr<Widget> operator[](const int index) const { return _children[index]; }
		std::shared_ptr<Widget> getChild(const int index) const { return _children[index]; }
		std::shared_ptr<Widget> getChildByName(const std::string& name) const { return *std::find_if(_children.begin(), _children.end(), [&name] (std::shared_ptr<Widget> widget) {return widget->_name == name; }); }

	protected:
		std::vector<std::shared_ptr<Widget>> _children;
		bool _visible;
		std::string _name;

	private:
		//to get rid of cryptic error messages.
		Widget(Widget const&);
		void operator=(Widget const&);
	};
}

#endif