#include <SFML\Graphics\RenderTarget.hpp>
#include <Thor\Resources\SfmlLoaders.hpp>

#include "Menu.hpp"
#include "..\Game.hpp"

gui::Menu::Menu(std::vector<std::string>& menuItems, unsigned int size)
: _font(Game::Cache->acquire(thor::Resources::fromFile<sf::Font>("assets/fonts/kenpixel_high_square.ttf")))
, _menuItems(0)
, _selected(0)
, _size(size)
{
	for (size_t i = 0; i < menuItems.size(); i++)
	{
		add(menuItems[i]);
	}
}

gui::Menu::Menu()
: _font(Game::Cache->acquire(thor::Resources::fromFile<sf::Font>("assets/fonts/kenpixel_high_square.ttf")))
, _menuItems(0)
, _selected(0)
{

}

void gui::Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states = getTransform();
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
	if (_menuItems.empty())//highlight first item as selected.
		t->setColour(sf::Color::Cyan);
	_menuItems.push_back(std::move(t));
}

void gui::Menu::remove(const unsigned int index)
{
	//todo: not be lazy.
}

void gui::Menu::next()
{
	_menuItems[_selected]->setColour(sf::Color::White);
	_selected = _selected + 1 >= _menuItems.size() ? 0 : _selected + 1;
	_menuItems[_selected]->setColour(sf::Color::Cyan);
}

void gui::Menu::prev()
{
	_menuItems[_selected]->setColour(sf::Color::White);
	_selected = _selected == 0 ? _menuItems.size() - 1 : _selected - 1;
	_menuItems[_selected]->setColour(sf::Color::Cyan);
}

std::unique_ptr<gui::Label> gui::Menu::operator[](const int index)
{
	return std::move(_menuItems[index]);
}
