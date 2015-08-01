#include "base-agent.hh"

#include "utils.hh"

BaseAgent::BaseAgent(HQAgent* hq)
	: hq_(hq)
{
}

void
BaseAgent::run()
{
}

void
BaseAgent::associate_worker(WorkerAgent* w)
{
	workers_.insert(w);
}

void
BaseAgent::create_pylon()
{
	BWAPI::TilePosition p = utils::find_valid_location_circle(hq_->unit()->getPosition(), 320, BWAPI::UnitTypes::Protoss_Pylon);
	WorkerAgent* w = *workers_.begin();
	std::cout << hq_->unit()->getPosition() << " |||| " << p << std::endl;

	std::cout << BWAPI::Broodwar->canBuildHere(p, BWAPI::UnitTypes::Protoss_Pylon, nullptr, true) << std::endl;
	if (BWAPI::Broodwar->self()->minerals() >= BWAPI::UnitTypes::Protoss_Pylon.mineralPrice())
	{
		//w->unit()->move(static_cast<BWAPI::Position>(p));
		std::cout << w->unit()->build(BWAPI::UnitTypes::Protoss_Pylon, p) << std::endl;
	}
}