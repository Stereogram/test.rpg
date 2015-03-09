#include <SFML/Graphics/Texture.hpp>
#include <Thor/Animation/FrameAnimation.hpp>

#include "AnimatedSprite.hpp"
#include "../Game.hpp"


AnimatedSprite::AnimatedSprite(const thor::ResourceKey<sf::Texture> textureKey, const sf::Vector2u size, std::vector<Animation>& animations)
: _sprite(*Game::Cache->acquire(textureKey))
, _size(size)
, _tsize(_sprite.getTexture()->getSize())
, _animations(animations)
{
	addFrames();
	_animator.playAnimation(_animations[0].Name, true);
}

AnimatedSprite::AnimatedSprite()
{

}

void AnimatedSprite::play(const std::string& anim, const bool loop)
{
	_animator.playAnimation(anim, loop);
}

void AnimatedSprite::stop()
{
	_animator.stopAnimation();
}

std::string AnimatedSprite::currentAnimation() const
{
	return _animator.isPlayingAnimation() ? _animator.getPlayingAnimation() : "none";
}

void AnimatedSprite::update(const sf::Time& dt)
{
	_animator.update(dt);
	_animator.animate(_sprite);
}

void AnimatedSprite::addFrames()
{
	int total = 0;
	for (Animation anim : _animations)
	{
		thor::FrameAnimation temp;
		for (int i = 0; i < anim.Frames; i++, total++)
		{
			int tu = (int)((total % (_tsize.x / _size.y)) * _size.x);
			int tv = (int)((total / (_tsize.y / _size.y)) * _size.y);
			temp.addFrame(1, sf::IntRect(tu, tv, _size.x, _size.y));
		}
		_animator.addAnimation(anim.Name,temp,anim.Duration);
	}
}

void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite);
}
