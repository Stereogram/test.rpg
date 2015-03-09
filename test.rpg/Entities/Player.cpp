#include "Player.hpp"

Player::Player()
: Party()
{

}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}

Player::~Player()
{
	Party.clear();
}
