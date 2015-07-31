#ifndef AGENT_HH_
# define AGENT_HH_

# include <set>

class Agent
{
public:

	const std::set<Agent*>& sub_agents_get() const;

	void run();

protected:

	virtual void internal_run() = 0;

private:

	std::set<Agent*> sub_agents_;
};

#include "agent.hxx"

#endif