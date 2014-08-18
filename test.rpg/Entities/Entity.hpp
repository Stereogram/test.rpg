#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <memory>
#include <functional>

#include <SFML\Graphics.hpp>
#include <Thor\Resources\ResourceKey.hpp>

#include "..\Util\AnimatedSprite.hpp"
#include "Stats.hpp"


class Entity : public sf::Drawable, sf::Transformable
{
public:
	Entity(thor::ResourceKey<sf::Texture>, sf::Vector2u, std::unique_ptr<std::vector<Animation>>);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	Stats& getStats() { return _stats; }
	std::unique_ptr<std::vector<std::pair<std::string, std::function<void(std::vector<Entity*>)>>>> getActions() { return std::move(_actions); }

	std::string Name;

private:
	AnimatedSprite _sprite;
	Stats _stats;
	std::unique_ptr<std::vector<std::pair<std::string, std::function<void(std::vector<Entity*>)>>>> _actions;
};

#endif // ENTITY_HPP
