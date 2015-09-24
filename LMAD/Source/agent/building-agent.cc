#include "building-agent.hh"

#include "requests/request.hh"

BuildingAgent::BuildingAgent(BWAPI::Unit u)
	: UnitAgent(u)
{

}

void BuildingAgent::protected_on_frame()
{

}

VISIT_DEFINITIONS(BuildingAgent);