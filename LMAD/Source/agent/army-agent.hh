#ifndef ARMY_AGENT_HH_
# define ARMY_AGENT_HH_

# include "agent.hh"
# include "unit-agent.hh"

class ArmyAgent : public Agent, public UnitAgent
{
public:

	ArmyAgent(const BWAPI::Unit& u);

	virtual void run() override;
};

# include "army-agent.hxx"

#endif