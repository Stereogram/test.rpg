#include <Thor/Animation.hpp>
#include <Thor/Resources.hpp>
#include "SFML/Graphics/Sprite.hpp"
#include <memory>
#include "Animation.hpp"

class AnimatedSprite
{
public:
	AnimatedSprite(thor::ResourceKey<sf::Texture>, sf::Vector2u, std::unique_ptr<std::vector<Animation>>);
	void play(std::string, bool);
	void stop();
	std::string currentAnimation();
	void update(sf::Time);

private:
	void addFrames();

	std::unique_ptr<std::vector<Animation>> _animations;
	sf::Vector2u _size;
	std::shared_ptr<sf::Texture> _texture;
	thor::Animator<sf::Sprite, std::string> _animator;
};