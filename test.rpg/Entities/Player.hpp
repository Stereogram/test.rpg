#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <memory>
#include <vector>

#include <SFML\Graphics\Drawable.hpp>

#include "..\Entities\Entity.hpp"

class Player : sf::Drawable
{
public:
	Player();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	std::unique_ptr<std::vector<Entity*>> Party;
private:
	
};

#endif