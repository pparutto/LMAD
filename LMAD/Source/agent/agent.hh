#ifndef AGENT_HH_
# define AGENT_HH_

# include <utility>
# include <set>
# include <queue>

# include <BWAPI/unit.h>

class Request;

# include "requests/requests-fw.hh"

class UnitAgent;

class Agent
{
public:

	Agent();
	virtual ~Agent();

	void request(Request* r); // priority is between 0 & 100

	void on_unit_created(UnitAgent* u);
	void on_unit_completed(UnitAgent* u);
	void on_unit_destroyed(UnitAgent* u);

	/**
		REQUESTS BEGIN
	**/
	
	virtual void accept(Request* r);
	virtual void accept(PylonRequest* r);

	/**
		REQUESTS END
	**/

	void on_frame();

	void init();
	void clear();

public:

	void parent_set(Agent* parent);
	Agent* parent_get() const;

	void add_sub_agent(Agent* agent);
	void remove_sub_agent(Agent* agent);

protected:

	virtual void protected_on_unit_created(UnitAgent* u);
	virtual void protected_on_unit_completed(UnitAgent* u);
	virtual void protected_on_unit_destroyed(UnitAgent* u);

	virtual void protected_on_frame() = 0;

	virtual void protected_init();
	virtual void protected_clear();

	void try_request(Request* r);
	void on_request_ended(Request* r);

private:

	Agent* parent_;
	std::queue<Request*> requests_to_remove_;
	std::set<Request*> requests_;
	std::set<Agent*> sub_agents_;
};

#include "agent.hxx"

#endif