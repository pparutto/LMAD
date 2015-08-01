#ifndef BASE_AGENT_HH_
# define BASE_AGENT_HH_

# include "hq-agent.hh"
# include "worker-agent.hh"
# include "agent.hh"

# include <BWAPI.h>

class BaseAgent : public Agent
{
public:
	BaseAgent(HQAgent* hq);

	virtual void run() override;

	void associate_worker(WorkerAgent* w);
	void create_pylon();

private:
	HQAgent* hq_;
	std::set<WorkerAgent*> workers_;
};

#endif /// !BASE_AGENT_HH_