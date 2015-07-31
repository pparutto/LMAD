#ifndef ARMY_AGENT_HH_
# define ARMY_AGENT_HH_

# include "agent.hh"

class ArmyAgent : public Agent
{
public:

	virtual void run() override;
};

# include "army-agent.hxx"

#endif