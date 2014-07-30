#include "AnimatedSprite.hpp"
#include <SFML/Graphics/Texture.hpp>

AnimatedSprite::AnimatedSprite(thor::ResourceKey<sf::Texture> textureKey, sf::Vector2u size, std::unique_ptr<std::vector<Animation>> animations) : _size(size)
{
	_animations = std::move(animations);
	//_texture = Game::Cache.acquire(textureKey);
}

void AnimatedSprite::play(std::string anim, bool loop)
{
	_animator.playAnimation(anim, loop);
}

void AnimatedSprite::stop()
{
	_animator.stopAnimation();
}

std::string AnimatedSprite::currentAnimation()
{
	return _animator.isPlayingAnimation() ? _animator.getPlayingAnimation() : "null";
}

void AnimatedSprite::update(sf::Time dt)
{
	_animator.update(dt);
}

void AnimatedSprite::addFrames()
{
	int total = 0;
	for (Animation anim : *_animations)
	{
		thor::FrameAnimation temp;
		for (int i = 0; i < anim.Frames; i++, total++)
		{
			int tu = (int)((total % (_texture->getSize().x / _size.y)) * _size.x);
			int tv = (int)((total / (_texture->getSize().y / _size.y)) * _size.y);
			temp.addFrame(1, sf::IntRect(tu, tv, _size.x, _size.y));
		}
		_animator.addAnimation(anim.Name,temp,sf::seconds(1));
	}
}