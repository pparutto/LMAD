#ifndef WORKER_AGENT_HH_
# define WORKER_AGENT_HH_

# include "eco-agent.hh"
# include "unit-agent.hh"

# include <BWAPI.h>

class WorkerAgent : public EcoAgent, public UnitAgent
{
public:
	WorkerAgent(const BWAPI::Unit u);

protected:

	virtual void protected_run() override;

protected:
	bool is_collecting_;
};

#endif /// !WORKER_AGENT_HH_