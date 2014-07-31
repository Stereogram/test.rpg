#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <memory>
#include <SFML\Graphics.hpp>
#include <Thor\Resources\ResourceKey.hpp>
#include "..\Util\AnimatedSprite.hpp"
#include "..\States\Stats.hpp"

class Entity : public sf::Drawable, sf::Transformable
{
public:
	Entity(thor::ResourceKey<sf::Texture>, sf::Vector2u, std::unique_ptr<std::vector<Animation>>);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	AnimatedSprite _sprite;
	Stats _stats;
};

#endif // ENTITY_HPP
