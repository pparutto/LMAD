#include "army-agent.hh"
#include "../utils/game-info.hh"

#include <iostream>

ArmyAgent::ArmyAgent(BWAPI::Unit u)
	: UnitAgent(u)
	, line_to_scout_(0)
{

}

void ArmyAgent::protected_on_frame()
{
	// trying to scout for fun.
	GameInfo* info = GameInfo::instance_get();
	const std::set<MineralLine*>& mineral_lines = info->mineral_lines_get();

	bool has_reached_line = false;

	if (line_to_scout_)
	{
		std::cout << line_to_scout_->center_get() << ":" << unit_get()->getPosition() << std::endl;
	}

	if (line_to_scout_ && (line_to_scout_->center_get() == unit_get()->getPosition()))
	{
		has_reached_line = true;
	}

	if (!mineral_lines.size())
	{
		return;
	}

	if (!line_to_scout_)
	{
		line_to_scout_ = *(mineral_lines.begin());
	}
	else if (has_reached_line)
	{
		bool was_last = false;
		for (auto l : mineral_lines)
		{
			if (was_last)
			{
				line_to_scout_ = l;
				break;
			}
			if (l == line_to_scout_)
			{
				was_last = true;
			}
		}
	}

	if (line_to_scout_)
	{
		unit_get()->move(line_to_scout_->center_get());
	}
}
