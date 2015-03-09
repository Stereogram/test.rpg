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
	~Player();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	std::vector<std::shared_ptr<Entity>> Party;
private:
	//todo: inventory.
};

#endif