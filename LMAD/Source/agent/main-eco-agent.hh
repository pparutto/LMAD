#ifndef MAIN_ECO_AGENT_
# define MAIN_ECO_AGENT_

# include <set>

# include <BWAPI/Unit.h>

# include "agent.hh"
# include "eco-agent.hh"

# include "worker-agent.hh"
# include "hq-agent.hh"

# include "base-agent.hh"

class MainEcoAgent : public Agent
{
public:

	MainEcoAgent();

	void init();

	void add_worker(const BWAPI::Unit& u);
	void add_HQ(const BWAPI::Unit& u);

protected:

	virtual void protected_run() override;

private:
	std::set<EcoAgent*> eco_agents_;
	std::set<WorkerAgent*> waiting_workers_;
	std::set<BaseAgent*> bases_;
};

# include "main-eco-agent.hxx"

#endif