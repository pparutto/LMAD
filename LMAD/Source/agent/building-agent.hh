#ifndef BUILDING_AGENT_HH_
# define BUILDING_AGENT_HH_

# include "unit-agent.hh"

class BuildingAgent : public UnitAgent
{
public:
	BuildingAgent(BWAPI::Unit u);

	VISIT_DECLARATIONS;

protected:
	virtual void protected_on_frame() override;
};

#endif