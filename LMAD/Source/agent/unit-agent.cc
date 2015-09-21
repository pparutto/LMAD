#include "unit-agent.hh"

UnitAgent::UnitAgent(BWAPI::Unit unit)
	: unit_(unit)
{

}

UnitAgent::~UnitAgent()
{
	unit_ = nullptr;
}

void UnitAgent::protected_clear()
{
	unit_ = nullptr;
}