#include "hq-agent.hh"

#include <BWAPI.h>

#include "../utils/game-info.hh"
#include "requests/request.hh"

HQAgent::HQAgent(BWAPI::Unit u)
	: BuildingAgent(u)
{
}

HQAgent::~HQAgent()
{
}

void
HQAgent::protected_on_frame()
{
}

VISIT_DEFINITIONS(HQAgent);