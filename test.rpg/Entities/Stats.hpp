struct Stat
{
public:
	Stat(unsigned int max) : _max(max), _current(max)
	{
	}
	void increase(const unsigned int amount)
	{
		_current = _current + amount >= _max ? _max : _current + amount;
	}
	void decrease(const unsigned int amount)
	{
		_current = static_cast<signed int>(_current - amount) <= 0 ? 0 : _current - amount;
	}
	void setMax(const unsigned int amount)
	{
		_max = amount;
	}
	float getPercent()
	{
		return static_cast<float>(_current) / static_cast<float>(_max);
	}
	static std::string to_string(Stat& s) { return std::to_string(s._current) + "/" + std::to_string(s._max); }
	unsigned int getMax() { return _max; }
	unsigned int getCurrent() { return _current; }
private:
	unsigned int _current;
	unsigned int _max;
};

struct Stats
{
public:
	Stats(unsigned int health, unsigned int mana) : Health(health), Mana(mana), Strength(1), Agility(1), Intelligence(1), Level(1)
	{
	}
	unsigned int Strength;
	unsigned int Agility;
	unsigned int Intelligence;
	unsigned int Level;
	Stat Health;
	Stat Mana;
};