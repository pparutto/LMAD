#ifndef MAIN_ECO_AGENT_
# define MAIN_ECO_AGENT_

# include <set>

# include <BWAPI/Unit.h>

# include "agent.hh"
# include "eco-agent.hh"

# include "worker-agent.hh"
# include "hq-agent.hh"

class MainEcoAgent : public Agent
{
public:

	virtual void run() override;

	void add_worker(const BWAPI::Unit u);
	void add_HQ(const BWAPI::Unit u);

private:
	std::set<EcoAgent*> eco_agents_;
	std::set<WorkerAgent*> workers_;
	std::set<HQAgent*> HQs_;
};

# include "main-eco-agent.hxx"

#endif