#ifndef BASE_AGENT_HH_
# define BASE_AGENT_HH_

# include "hq-agent.hh"
# include "agent.hh"

# include <BWAPI.h>

class BaseAgent : public Agent
{
public:
	BaseAgent(const BWAPI::Unit hq);

	virtual void run() override;

	void create_pylon();

private:
	HQAgent hq_;
};

#endif /// !BASE_AGENT_HH_