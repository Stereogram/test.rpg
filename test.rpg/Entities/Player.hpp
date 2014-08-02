#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML\Graphics\Drawable.hpp>
#include <vector>
#include <memory>
#include "..\Entities\Entity.hpp"

class Player : sf::Drawable
{
public:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	std::vector<std::unique_ptr<Entity>> _party;
};

#endif