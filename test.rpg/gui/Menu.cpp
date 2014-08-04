#include <SFML\Graphics\RenderTarget.hpp>
#include <Thor\Resources\SfmlLoaders.hpp>

#include "Menu.hpp"
#include "..\Game.hpp"

gui::Menu::Menu(std::unique_ptr<Box> box, std::vector<std::string>& menuItems)
: _box(std::move(box))
, _font(Game::Cache->acquire(thor::Resources::fromFile<sf::Font>("assets/fonts/kenpixel_high_square.ttf")))
, _menuItems(0)
, _selected(0)
{
	for (size_t i = 0; i < menuItems.size(); i++)
	{
		auto t = std::unique_ptr<gui::Label>(new Label(*_font, menuItems[i]));
		t->setPosition(20.f, (30.f*i) + 20.f);//hardcoded positions ftw.
		_menuItems.push_back(std::move(t));
	}
}

void gui::Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*_box, states);
	for (const auto& item : _menuItems)
	{
		item->draw(target, states);
	}
	for (const auto& child : _children)
	{
		child->draw(target, states);
	}
}

void gui::Menu::add(const std::string& item)
{
	auto t = std::unique_ptr<gui::Label>(new Label(*_font, item));
	t->setPosition(20.f, (30.f*_menuItems.size()) + 20.f);//hardcoded positions ftw.
	_menuItems.push_back(std::move(t));
}

void gui::Menu::remove(const unsigned int index)
{
	//todo: not be lazy.
}

void gui::Menu::next()
{
	_selected = _selected + 1 >= _menuItems.size() ? 0 : _selected + 1;
}

void gui::Menu::prev()
{
	_selected = _selected == 0 ? _menuItems.size() - 1 : _selected - 1;
}