#ifndef HQ_AGENT_HH_
# define HQ_AGENT_HH_

# include "building-agent.hh"

class HQAgent : public BuildingAgent
{
public:

	HQAgent(BWAPI::Unit u);
	virtual ~HQAgent();

	VISIT_DECLARATIONS;

protected:

	virtual void protected_on_frame() override;
};

# include "hq-agent.hxx"

#endif /// !GATE_AGENT_HH_