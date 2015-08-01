#ifndef AGENT_HH_
# define AGENT_HH_

class Request;

class Agent
{
public:

	void request(Request* r);

	virtual void accept(Request* r);

	virtual void run() = 0;
};

#include "agent.hxx"

#endif