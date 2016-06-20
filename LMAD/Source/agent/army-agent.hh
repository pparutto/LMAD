#ifndef ARMY_AGENT_HH_
# define ARMY_AGENT_HH_

# include "unit-agent.hh"

# include "../utils/game-info.hh"

class ArmyAgent : public UnitAgent
{
public:

	ArmyAgent(BWAPI::Unit u);

	VISIT_DECLARATIONS;

	void mode_set(unsigned mode);
	const unsigned mode_get() const;

	void first_pos_set(BWAPI::Position pos);
	void second_pos_set(BWAPI::Position pos);

	const bool has_finished_order_get() const;

	void target_set(BWAPI::Unit target);
	BWAPI::Unit target_get() const;

	enum Mode
	{
		NONE = 0,
		SCOUT,
		ATTACK,
		DEFEND,
		PATROL
	};

protected:

	virtual void protected_on_frame() override;
	virtual void protected_on_enemy_unit_destroyed(BWAPI::Unit u) override;

private:

	unsigned mode_;
	BWAPI::Position first_pos_;
	BWAPI::Position second_pos_;
	bool has_finished_order_;
	BWAPI::Unit target_;
};

# include "army-agent.hxx"

#endif