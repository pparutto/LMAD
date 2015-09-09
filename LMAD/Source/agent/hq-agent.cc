#include "hq-agent.hh"

#include <BWAPI.h>

HQAgent::HQAgent(const BWAPI::Unit u)
	: UnitAgent(u)
{
}

void
HQAgent::protected_run()
{
}

bool HQAgent::train_worker() const
{
	if (is_training())
	{
		return false;
	}
	if (BWAPI::Broodwar->self()->minerals() >= BWAPI::UnitTypes::Protoss_Probe.mineralPrice())
	{
		unit_get()->train(BWAPI::Broodwar->self()->getRace().getWorker());
		if (is_training())
		{
			return true;
		}
	}

	return false;
}