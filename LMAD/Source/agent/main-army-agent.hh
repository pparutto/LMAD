#ifndef MAIN_ARMY_AGENT_HH_
# define MAIN_ARMY_AGENT_HH_

# include "meta-agent.hh"
# include "army-agent.hh"

# include "building-agent.hh"

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

	virtual void protected_on_unit_completed(BuildingAgent* u) override;
	virtual void protected_on_unit_destroyed(BuildingAgent* u) override;

	virtual void protected_on_unit_show(BWAPI::Unit u) override;
private:

	void scout();

private:
	
	std::set<ArmyAgent*> army_agents_;

	std::set<BuildingAgent*> gates_;
	BuildingAgent* core_;

	std::set<BWAPI::TilePosition> possible_spawns_;

	bool has_dragoon_range_started_;
	bool has_dragoon_range_finished_;
};

#endif