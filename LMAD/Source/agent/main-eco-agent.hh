#ifndef MAIN_ECO_AGENT_
# define MAIN_ECO_AGENT_

# include <set>

# include <BWAPI/Unit.h>

# include "meta-agent.hh"
# include "eco-agent.hh"

# include "worker-agent.hh"
# include "hq-agent.hh"

# include "base-agent.hh"

# include "requests/requests.hh"

class MainEcoAgent : public MetaAgent
{
public:

	MainEcoAgent();

	void add_worker(BWAPI::Unit u);
	void add_HQ(BWAPI::Unit u);

protected:

	virtual void protected_on_unit_created(UnitAgent* u) override;
	virtual void protected_on_unit_completed(UnitAgent* u) override;
	virtual void protected_on_unit_destroyed(UnitAgent* u) override;

	virtual void protected_init() override;
	virtual void protected_clear() override;

	virtual void protected_on_frame() override;

private:
	std::set<EcoAgent*> eco_agents_;
	std::set<WorkerAgent*> waiting_workers_;
	std::set<BaseAgent*> bases_;

	PylonRequest* r_;
};

# include "main-eco-agent.hxx"

#endif