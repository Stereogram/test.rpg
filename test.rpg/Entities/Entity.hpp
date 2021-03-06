#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <memory>
#include <functional>

#include <SFML\Graphics.hpp>
#include <Thor\Resources\ResourceKey.hpp>

#include "..\Util\AnimatedSprite.hpp"
#include "Stats.hpp"
#include "..\gui\Label.hpp"


class Entity : public sf::Drawable, sf::Transformable
{
public:
	Entity(thor::ResourceKey<sf::Texture>, sf::Vector2u, std::vector<Animation>&);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	Stats& getStats() { return _stats; }
	gui::Bar& getHealthBar() { return _healthBar; }
	gui::Bar& getManaBar() { return _manaBar; }
	gui::Label& getHealthLabel() { return _healthLabel; }
	gui::Label& getManaLabel() { return _manaLabel; }
	std::unique_ptr<std::vector<std::pair<std::string, std::function<void(std::vector<Entity*>)>>>> getActions() { return std::move(_actions); }

	std::string Name;

private:
	AnimatedSprite _sprite;
	Stats _stats;
	gui::Bar _healthBar;
	gui::Bar _manaBar;
	gui::Label _healthLabel;
	gui::Label _manaLabel;

	std::unique_ptr<std::vector<std::pair<std::string, std::function<void(std::vector<Entity*>)>>>> _actions;
	Entity(Entity const&);
	void operator=(Entity const&);
};

#endif // ENTITY_HPP
