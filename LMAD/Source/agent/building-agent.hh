#ifndef BUILDING_AGENT_HH_
# define BUILDING_AGENT_HH_

# include "unit-agent.hh"

class BuildingAgent : public UnitAgent
{
public:
	BuildingAgent(const BWAPI::Unit& u);


protected:
	virtual void protected_on_frame() override;
};

#endif