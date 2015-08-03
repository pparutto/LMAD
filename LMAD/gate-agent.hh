#ifndef GATE_AGENT_HH_
# define GATE_AGENT_HH_

# include "building-agent.hh"
# include "unit-agent.hh"

class HQAgent : public BuildingAgent, public UnitAgent
{
public:
	HQAgent(const BWAPI::Unit u);

	virtual void run();
};

#endif /// !GATE_AGENT_HH_