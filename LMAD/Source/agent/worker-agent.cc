#include "worker-agent.hh"

#include "utils.hh"

WorkerAgent::WorkerAgent(const BWAPI::Unit& u)
	: UnitAgent(u)
	, is_collecting_(false)
	, has_orders_(false)
{
}

void
WorkerAgent::protected_on_frame()
{
	bool is_constructing = unit_get()->isConstructing();
	if (!is_collecting_ && !is_constructing && !has_orders_)
	{
		const BWAPI::Unit mine = utils::closest_unit(BWAPI::Broodwar->getMinerals(), unit_get());
		unit_get()->rightClick(mine);
		is_collecting_ = true;
	}
	if (is_constructing)
	{
		is_collecting_ = false;
	}
}
