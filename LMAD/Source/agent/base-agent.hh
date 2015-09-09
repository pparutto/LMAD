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
	~BaseAgent();

	void associate_worker(WorkerAgent* w);
	void create_pylon();
	void create_gate();

	void set_max_workers(const unsigned mineral, const unsigned gas);

protected:

	virtual void protected_run() override;

private:
	HQAgent* hq_;
	std::set<WorkerAgent*> workers_;
	std::set<BWAPI::Unit> pylons_;

	unsigned max_mineral_;
	unsigned max_gas_;

	bool is_building_pylon_;

};

# include "base-agent.hxx"

#endif /// !BASE_AGENT_HH_