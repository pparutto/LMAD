#ifndef MAIN_ARMY_AGENT_HH_
# define MAIN_ARMY_AGENT_HH_

# include "agent.hh"
# include "army-agent.hh"

# include <set>

# include <BWAPI/Region.h>

class MainArmyAgent : public Agent
{
public:

	MainArmyAgent();

	virtual void run() override;

	void add_unit(const BWAPI::Unit& u);

private:
	void scout();

private:
	
	std::set<ArmyAgent*> army_agents_;
};

#endif