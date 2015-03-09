#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <string>
#include <SFML\System\Time.hpp>
#include <fstream>

class Animation
{
public:
	const std::string Name;
	const int Frames;
	const sf::Time Duration;

	Animation(const std::string& name, const int frames, const float duration)
	: Name(name)
	, Frames(frames)
	, Duration(sf::seconds(duration))
	{
	}

	static std::vector<Animation>& readAnimation(const std::string& fileName)
	{
		std::vector<Animation>* v = new std::vector<Animation>();
		std::ifstream file(fileName);
		int frames;
		std::string name;
		float duration;
		while (file >> name >> frames >> duration)
		{
			v->push_back(Animation(name, frames, duration));
		}
		return *v;
	}

};

#endif