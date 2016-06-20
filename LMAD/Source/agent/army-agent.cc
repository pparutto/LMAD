#include "army-agent.hh"
#include "../utils/game-info.hh"

#include "requests/request.hh"

#include <iostream>

ArmyAgent::ArmyAgent(BWAPI::Unit u)
	: UnitAgent(u)
	, mode_(NONE)
	, target_(nullptr)
{

}

void ArmyAgent::protected_on_frame()
{
	switch (mode_)
	{
		case NONE:
		{
			break;
		}
		case SCOUT:
		{
			if (can_see_position(first_pos_))
			{
				unit_get()->stop();
				has_finished_order_ = true;
			}
			else
			{
				move(first_pos_);
			}
			break;
		}
		case ATTACK:
		{
			if (target_)
			{
				attack(target_);
			}
			else
			{
				attack(first_pos_);
			}
			break;
		}
		case DEFEND:
		{
			move(first_pos_);
			break;
		}
		case PATROL:
		{
			move(first_pos_);
			break;
		}
	}
}

void ArmyAgent::protected_on_enemy_unit_destroyed(BWAPI::Unit u)
{
	if (u == target_)
	{
		target_ = nullptr;
	}
}

VISIT_DEFINITIONS(ArmyAgent);