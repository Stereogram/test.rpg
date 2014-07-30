#include <string>

struct Animation
{
	std::string Name;
	int Frames;
	Animation(std::string name, int frames)
	{
		Name = name;
		Frames = frames;
	}
};