#ifndef ARMY_AGENT_HH_
# define ARMY_AGENT_HH_

# include "unit-agent.hh"

# include "../utils/game-info.hh"

class ArmyAgent : public UnitAgent
{
public:

	ArmyAgent(const BWAPI::Unit& u);

protected:

	virtual void protected_run() override;

private:

	MineralLine* line_to_scout_;
};

# include "army-agent.hxx"

#endif