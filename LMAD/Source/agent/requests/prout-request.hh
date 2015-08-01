#ifndef PROUT_REQUEST_HH_
# define PROUT_REQUEST_HH_

# include "request.hh"

class ProutRequest : public Request
{
public:
	virtual void visit(Agent* agent) override;
};

#endif