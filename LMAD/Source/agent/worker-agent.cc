#include "worker-agent.hh"

#include "utils.hh"

WorkerAgent::WorkerAgent(const BWAPI::Unit u)
	: UnitAgent(u)
	, is_collecting_(false)
{
}

void
WorkerAgent::protected_run()
{
	bool is_constructing = unit_get()->isConstructing();
	if (!is_collecting_ && !is_constructing)
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
