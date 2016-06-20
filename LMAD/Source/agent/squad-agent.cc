#include "squad-agent.hh"

void SquadAgent::add_unit(ArmyAgent* u)
{
	BWAPI::UnitType t = u->unit_get()->getType();
	if (t == BWAPI::UnitTypes::Protoss_Zealot)
	{
		zealots_.insert(u);
	}
	else if (t == BWAPI::UnitTypes::Protoss_Dragoon)
	{
		dragoons_.insert(u);
	}
}

void SquadAgent::protected_on_frame()
{
	switch (mode_)
	{
		case NONE:
		{
			break;
		}
		case ATTACK:
		{
			break;
		}
		case DEFEND:
		{
			break;
		}
	}
}

void SquadAgent::protected_on_unit_destroyed(ArmyAgent* u)
{
	if (zealots_.find(u) != zealots_.end())
	{
		zealots_.erase(u);
	}
	else if (dragoons_.find(u) != dragoons_.end())
	{
		dragoons_.erase(u);
	}
}