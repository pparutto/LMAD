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

	void add_unit(BWAPI::Unit u);

protected:

	virtual void protected_on_unit_created(UnitAgent* u) override;
	virtual void protected_on_unit_completed(UnitAgent* u) override;
	virtual void protected_on_unit_destroyed(UnitAgent* u) override;

	virtual void protected_init() override;
	virtual void protected_clear() override;

	virtual void protected_on_frame() override;

private:
	void scout();

private:
	
	std::set<ArmyAgent*> army_agents_;
};

#endif