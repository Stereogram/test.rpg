#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <memory>
#include "SFML\Graphics.hpp"

class Entity : public sf::Drawable, sf::Transformable
{
public:
	Entity();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	

};

#endif // ENTITY_HPP
