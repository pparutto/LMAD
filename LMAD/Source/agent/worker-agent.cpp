#include "worker-agent.hh"

#include "utils.hh"

WorkerAgent::WorkerAgent(const BWAPI::Unit u)
	: UnitAgent(u)
	, is_collecting_(false)
{
}

void
WorkerAgent::run()
{
	if (!is_collecting_)
	{
		const BWAPI::Unit mine = utils::closest_unit(BWAPI::Broodwar->getMinerals(), unit_);
		unit_->rightClick(mine);
		is_collecting_ = true;
	}
}
