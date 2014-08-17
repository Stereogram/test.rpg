#include "Entity.hpp"
#include <SFML\Graphics.hpp>

Entity::Entity(thor::ResourceKey<sf::Texture> textureKey, sf::Vector2u size, std::unique_ptr<std::vector<Animation>> animations)
: _sprite(textureKey, size, std::move(animations))
, _stats(50, 50)
{

}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	throw std::logic_error("The method or operation is not implemented.");
}

