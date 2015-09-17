#ifndef REQUEST_HH_
# define REQUEST_HH_

# include "../unit-agent.hh"

# include "request-data.hh"

class Request
{
public:

#ifdef _DEBUG
	Request();
#endif

	virtual void visit(Agent* agent) = 0;

	void on_frame();

	RequestData* data_get() const;

	virtual void on_unit_created(UnitAgent* u);
	virtual void on_unit_completed(UnitAgent* u);
	virtual void on_unit_destroyed(UnitAgent* u);

protected:
	RequestData* data_;
};

# include "request.hxx"

#endif