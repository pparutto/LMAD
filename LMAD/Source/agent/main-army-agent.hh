#ifndef MAIN_ARMY_AGENT_HH_
# define MAIN_ARMY_AGENT_HH_

# include "agent.hh"
# include "army-agent.hh"

# include <set>

class MainArmyAgent : public Agent
{
public:

	virtual void run() override;

private:

	std::set<ArmyAgent*> army_agents_;
};

#endif