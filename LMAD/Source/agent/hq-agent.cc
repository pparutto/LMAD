#include "hq-agent.hh"

#include <BWAPI.h>

#include "../utils/game-info.hh"
#include "requests/request.hh"

HQAgent::HQAgent(BWAPI::Unit u)
	: UnitAgent(u)
	, has_money_(false)
{
}

HQAgent::~HQAgent()
{
}

void
HQAgent::protected_on_frame()
{
}

bool HQAgent::train_worker()
{
	if (is_training())
	{
		return false;
	}
	if (!has_money_)
	{
		has_money_ = GameInfo::instance_get()->bank_get()->request_mineral(50);
	}
	if (has_money_)
	{
		unit_get()->train(BWAPI::Broodwar->self()->getRace().getWorker());
		if (is_training())
		{
			has_money_ = false;
			return true;
		}
	}

	return false;
}

VISIT_DEFINITIONS(HQAgent);