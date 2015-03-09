#include "Entity.hpp"
#include <SFML\Graphics.hpp>

Entity::Entity(thor::ResourceKey<sf::Texture> textureKey, sf::Vector2u size, std::vector<Animation>& animations)
: _sprite(textureKey, size, animations)
, _stats(50, 50)
, _health(sf::Vector2f(100.f,20.f))
, _mana(sf::Vector2f(100.f, 20.f))
{

}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	throw std::logic_error("The method or operation is not implemented.");
}

