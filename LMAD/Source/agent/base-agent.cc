#include "base-agent.hh"

#include "utils.hh"

BaseAgent::BaseAgent(HQAgent* hq)
	: hq_(hq)
{
	set_max_workers(16, 0);
}

BaseAgent::~BaseAgent()
{
	delete hq_;
	for (auto w : workers_)
	{
		delete w;
	}
}

void
BaseAgent::protected_run()
{
	if (workers_.size() < max_mineral_)
	{
		hq_->train_worker();
	}

	hq_->run();

	for (auto w : workers_)
	{
		w->run();
	}

	// FIXME : 2 sucks, it should be a dynamic value.
	if (BWAPI::Broodwar->self()->supplyTotal() - BWAPI::Broodwar->self()->supplyUsed() <= 2)
	{
		create_pylon();
	}

}

void
BaseAgent::associate_worker(WorkerAgent* w)
{
	workers_.insert(w);
}

void
BaseAgent::create_pylon()
{
	BWAPI::TilePosition p = utils::find_valid_location_circle(hq_->unit_get()->getPosition(), 320, BWAPI::UnitTypes::Protoss_Pylon);
	WorkerAgent* w = *workers_.begin();
	//std::cout << hq_->unit()->getPosition() << " |||| " << p << std::endl;

	//std::cout << BWAPI::Broodwar->canBuildHere(p, BWAPI::UnitTypes::Protoss_Pylon, nullptr, true) << std::endl;
	if (BWAPI::Broodwar->self()->minerals() >= BWAPI::UnitTypes::Protoss_Pylon.mineralPrice())
	{
		//w->unit()->move(static_cast<BWAPI::Position>(p));
		//std::cout << w->unit()->build(BWAPI::UnitTypes::Protoss_Pylon, p) << std::endl;
		w->unit_get()->build(BWAPI::UnitTypes::Protoss_Pylon, p);
	}
}

void 
BaseAgent::create_gate()
{
	//BWAPI::TilePosition p = utils::find_valid_location_circle((*pylons_.begin())->getPosition(), BWAPI::UnitTypes::Protoss_Pylon., BWAPI::UnitTypes::Protoss_Pylon);
}