#ifndef ANIMATEDSPRITE_HPP
#define ANIMATEDSPRITE_HPP

#include <memory>

#include <Thor/Animation/Animator.hpp>
#include <Thor/Resources/ResourceKey.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Animation.hpp"

class AnimatedSprite : public sf::Drawable, public sf::Transformable
{
public:
	AnimatedSprite(const thor::ResourceKey<sf::Texture>, const sf::Vector2u, std::unique_ptr<std::vector<Animation>>);
	void play(const std::string, const bool);
	void stop();
	std::string currentAnimation() const;
	void update(const sf::Time&);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	void addFrames();

	sf::Sprite _sprite;
	std::unique_ptr<std::vector<Animation>> _animations;
	sf::Vector2u _size;
	sf::Vector2u _tsize;
	thor::Animator<sf::Sprite, std::string> _animator;
};

#endif