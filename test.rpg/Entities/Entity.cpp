#include "Entity.hpp"
#include <SFML\Graphics.hpp>
#include "..\Game.hpp"

Entity::Entity(thor::ResourceKey<sf::Texture> textureKey, sf::Vector2u size, std::vector<Animation>& animations)
: _sprite(textureKey, size, animations)
, _stats(50, 50)
, _healthBar(sf::Vector2f(50.f, 10.f))
, _manaBar(sf::Vector2f(50.f, 10.f))
, _healthLabel(*Game::Font, Stat::to_string(_stats.Health), 16U)
, _manaLabel(*Game::Font, Stat::to_string(_stats.Mana), 16U)
{

}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	throw std::logic_error("The method or operation is not implemented.");
}

