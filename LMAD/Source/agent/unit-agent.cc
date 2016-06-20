#include <BWAPI.h>

#include "unit-agent.hh"
#include "../utils/utils.hh"

UnitAgent::UnitAgent(BWAPI::Unit unit)
	: unit_(unit)
	, last_frame_move_(0)
{

}

UnitAgent::~UnitAgent()
{
	unit_ = nullptr;
}

void UnitAgent::protected_clear()
{
	unit_ = nullptr;
}

bool UnitAgent::move(BWAPI::Position pos)
{
	if (unit_->getPosition() == pos)
	{
		return true;
	}

	int frame_count = BWAPI::Broodwar->getFrameCount();
	if (last_frame_move_ + 50 <= frame_count)
	{
		unit_->move(pos);
		last_frame_move_ = frame_count;
	}
	return false;
}

bool UnitAgent::attack(BWAPI::Position pos)
{
	if (unit_->getPosition() == pos)
	{
		return true;
	}

	int frame_count = BWAPI::Broodwar->getFrameCount();
	if (last_frame_move_ + 1000 <= frame_count)
	{
		unit_->attack(pos);
		last_frame_move_ = frame_count;
	}
	return false;
}

bool UnitAgent::attack(BWAPI::Unit u)
{
	int frame_count = BWAPI::Broodwar->getFrameCount();
	if (last_frame_move_ + 1000 <= frame_count)
	{
		unit_->attack(u);
		last_frame_move_ = frame_count;
	}
	return false;
}

bool UnitAgent::can_see_position(BWAPI::Position pos)
{
	int sight = unit_->getType().sightRange();
	return pos.getDistance(unit_->getPosition()) < sight;
}

bool UnitAgent::can_see_position(BWAPI::TilePosition pos)
{
	return can_see_position(utils::tile_to_pos(pos));
}

bool UnitAgent::can_see_unit(BWAPI::Unit u)
{
	return can_see_position(u->getPosition());
}

bool UnitAgent::is_in_range(BWAPI::Unit u)
{
	int min_range = 0;
	int max_range = 0;

	if (u->getType().isFlyer())
	{
		min_range = unit_->getType().airWeapon().minRange();
		max_range = unit_->getType().airWeapon().maxRange();
	}
	else
	{
		min_range = unit_->getType().groundWeapon().minRange();
		max_range = unit_->getType().groundWeapon().maxRange();
	}

	double dist = unit_->getPosition().getDistance(u->getPosition());

	if (dist >= min_range && dist <= max_range)
	{
		return true;
	}
	else
	{
		return false;
	}
}
