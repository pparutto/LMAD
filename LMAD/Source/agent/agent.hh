#ifndef AGENT_HH_
# define AGENT_HH_

# include <utility>
# include <set>

class Request;

class Agent
{
public:

	void request(Request* r, unsigned priority); // priority is between 0 & 100

	virtual void accept(Request* r, unsigned priority);

	virtual void run() = 0;

protected:

	void try_request(Request* r, unsigned priority);

private:

	std::set<std::pair<Request*, unsigned> > requests_;
};

#include "agent.hxx"

#endif