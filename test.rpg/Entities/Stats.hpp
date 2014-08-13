struct Stats
{
	stat Health;
	stat Mana;
	unsigned int Strength;
	unsigned int Agility;
	unsigned int Intelligence;
	unsigned int Level;
};

struct Stat
{
public:
	void increase(const unsigned int amount)
	{
		_current = _current + amount >= _max ? _max : _current + amount;
	}
	void decrease(const unsigned int amount)
	{
		_current = _current - amount <= 0 ? 0 : _current - amount;
	}
	void setMax(const unsigned int amount)
	{
		_max = amount;
	}
private:
	unsigned int _current;
	unsigned int _max;
};