#ifndef SQUAD_AGENT_HH_
# define SQUAD_AGENT_HH_

# include "meta-agent.hh"
# include "army-agent.hh"

# include <set>

class SquadAgent : public MetaAgent
{
public:

	void add_unit(ArmyAgent* u);

	enum Mode
	{
		NONE = 0,
		ATTACK,
		DEFEND
	};

	void mode_set(const unsigned mode);


protected:

	virtual void protected_on_frame() override;
	virtual void protected_on_unit_destroyed(ArmyAgent* a) override;

private:
	std::set<ArmyAgent*> zealots_;
	std::set<ArmyAgent*> dragoons_;
	unsigned mode_;
};

# include "squad-agent.hxx"

#endif