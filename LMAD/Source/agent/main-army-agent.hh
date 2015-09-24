#ifndef MAIN_ARMY_AGENT_HH_
# define MAIN_ARMY_AGENT_HH_

# include "meta-agent.hh"
# include "army-agent.hh"

# include <set>

# include <BWAPI/Region.h>

class MainArmyAgent : public MetaAgent
{
public:

	MainArmyAgent();


protected:
	virtual void protected_on_unit_completed(ArmyAgent* a) override;

	virtual void protected_init() override;
	virtual void protected_clear() override;

	virtual void protected_on_frame() override;

private:
	void scout();

private:
	
	std::set<ArmyAgent*> army_agents_;
};

#endif