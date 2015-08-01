#ifndef REQUESTS_HH_
# define REQUESTS_HH_

# include "request.hh"

class PylonRequest : public Request
{
public:

	virtual void visit(Agent* agent, unsigned priority) override;
};

#endif