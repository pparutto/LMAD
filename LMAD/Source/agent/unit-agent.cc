#include "unit-agent.hh"

UnitAgent::UnitAgent(const BWAPI::Unit u)
	: unit_(u)
{
}

const BWAPI::Unit UnitAgent::unit() const
{
	return unit_;
}