#ifndef BASE_AGENT_HH_
# define BASE_AGENT_HH_

# include "hq-agent.hh"
# include "worker-agent.hh"
# include "agent.hh"

# include "requests/requests-fw.hh"

# include <BWAPI.h>

# include "../utils/game-info.hh"


class BaseAgent : public Agent
{
public:

	BaseAgent(HQAgent* hq);
	~BaseAgent();

	void associate_worker(WorkerAgent* w);
	void create_pylon();
	void create_gate();

	void set_max_workers(const unsigned mineral, const unsigned gas);


	/**
		REQUESTS BEGIN
	**/
public:
	virtual void accept(PylonRequest* r);
	
	/**
		REQUESTS END
	**/

protected:

	virtual void protected_on_frame() override;

private:
	HQAgent* hq_;
	std::set<WorkerAgent*> workers_;
	//std::set<BWAPI::Unit> pylons_;

	unsigned max_mineral_;
	unsigned max_gas_;

	bool is_building_pylon_;


	MineralLine* mineral_line_;

};

# include "base-agent.hxx"

#endif /// !BASE_AGENT_HH_