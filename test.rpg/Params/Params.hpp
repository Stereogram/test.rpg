#ifndef BATTLEPARAMS
#define BATTLEPARAMS

#include <memory>
#include <vector>
#include "..\Entities\Entity.hpp"
#include "..\Entities\Player.hpp"


struct Params
{
	std::unique_ptr<Player> Player;
};

struct BattleParams : public Params
{
	std::unique_ptr<std::vector<Entity>> Enemies;
};

#endif

