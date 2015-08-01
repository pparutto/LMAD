#include "hq-agent.hh"

#include <BWAPI.h>

HQAgent::HQAgent(const BWAPI::Unit u)
	: UnitAgent(u)
{
}

void
HQAgent::run()
{
	if (BWAPI::Broodwar->self()->minerals() >= BWAPI::UnitTypes::Protoss_Probe.mineralPrice())
		unit_->train(BWAPI::Broodwar->self()->getRace().getWorker());
}