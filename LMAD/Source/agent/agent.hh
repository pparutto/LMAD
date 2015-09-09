#ifndef AGENT_HH_
# define AGENT_HH_

# include <utility>
# include <set>

# include <BWAPI/unit.h>

class Request;

class Agent
{
public:

	void request(Request* r, unsigned priority); // priority is between 0 & 100

	virtual void accept(Request* r, unsigned priority);

	void run();


public:

	void parent_set(Agent* parent);
	Agent* parent_get() const;

protected:

	virtual void protected_run() = 0;
	void try_request(Request* r, unsigned priority);

private:

	Agent* parent_;
	std::set<std::pair<Request*, unsigned> > requests_;
};

#include "agent.hxx"

#endif