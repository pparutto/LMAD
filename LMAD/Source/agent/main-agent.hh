#ifndef MAIN_AGENT_HH_
# define MAIN_AGENT_HH_

# include "unit-agent.hh"

# include "main-eco-agent.hh"
# include "main-army-agent.hh"

# include <BWAPI.h>
# include <BWAPI/Client.h>

# include <map>

class MainAgent : public Agent
{
public:

	MainAgent();
	~MainAgent();

	void handle_events();

	void run();

protected:

	virtual void protected_on_frame() override;
	virtual void protected_init() override;
	virtual void protected_clear() override;
	virtual void protected_on_unit_show(BWAPI::Unit u) override;
	virtual void protected_on_unit_hide(BWAPI::Unit u) override;

private:

	UnitAgent* get_agent_from_bwunit(BWAPI::Unit u) const;

private:

	bool game_started_;

	MainEcoAgent* eco_agent_;
	MainArmyAgent* army_agent_;

	std::map<int, UnitAgent*> unit_agents_by_id_;
};

# include "main-agent.hxx"

#endif