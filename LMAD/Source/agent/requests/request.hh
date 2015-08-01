#ifndef REQUEST_HH_
# define REQUEST_HH_

# include "../agent.hh"

class Request
{
public:

	virtual void visit(Agent* agent) = 0;
};

#endif