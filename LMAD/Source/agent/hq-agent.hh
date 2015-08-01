#ifndef HQ_AGENT_HH_
# define HQ_AGENT_HH_

# include "building-agent.hh"
# include "unit-agent.hh"

class HQAgent : public BuildingAgent, public UnitAgent
{
public:
	HQAgent(const BWAPI::Unit u);

	virtual void run();
};

#endif /// !HQ_AGENT_HH_