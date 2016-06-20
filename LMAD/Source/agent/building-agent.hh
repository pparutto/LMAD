#ifndef BUILDING_AGENT_HH_
# define BUILDING_AGENT_HH_

# include "unit-agent.hh"

class BuildingAgent : public UnitAgent
{
public:
	BuildingAgent(BWAPI::Unit u);

	VISIT_DECLARATIONS;
	const bool is_training() const;
	const bool is_researching() const;

	bool train_unit(BWAPI::UnitType u);
	bool research(BWAPI::UpgradeType t);

protected:
	virtual void protected_on_frame() override;

private:
	bool has_money_;
};

# include "building-agent.hxx"

#endif