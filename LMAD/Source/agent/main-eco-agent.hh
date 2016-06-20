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

protected:

	virtual void protected_on_unit_completed(WorkerAgent* u) override;
	virtual void protected_on_unit_completed(BuildingAgent* u) override;

	virtual void protected_init() override;
	virtual void protected_clear() override;

	virtual void protected_on_frame() override;


private:
	std::set<WorkerAgent*> waiting_workers_;
	std::set<BaseAgent*> bases_;

	BaseAgent* main_base_;

	BuildingRequest* r_;
	BuildingRequest* rg_;
	BuildingRequest* rga_;
	BuildingRequest* rgc_;
	BuildingRequest* rg2_;
	BuildingRequest* rg3_;
	BuildingRequest* exp_;
};

# include "main-eco-agent.hxx"

#endif