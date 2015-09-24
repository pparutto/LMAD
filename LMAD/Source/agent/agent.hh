#ifndef AGENT_HH_
# define AGENT_HH_

# include <utility>
# include <set>
# include <queue>

# include <BWAPI/unit.h>

class Request;

# include "requests/requests-fw.hh"

class UnitAgent;
class ArmyAgent;
class WorkerAgent;
class HQAgent;
class BuildingAgent;

# define HH_SUB_PROTECTED_UNIT_EVENT(event_type, UNIT_TYPE) \
	protected: \
	virtual void protected_on_unit_##event_type(UNIT_TYPE* a);

# define HH_SUB_UNIT_EVENT(event_type, UNIT_TYPE) \
	public: \
	void on_unit_##event_type(UNIT_TYPE* a);

# define HH_PROTECTED_UNIT_EVENT(UNIT_TYPE) \
	HH_SUB_PROTECTED_UNIT_EVENT(created, UNIT_TYPE); \
	HH_SUB_PROTECTED_UNIT_EVENT(completed, UNIT_TYPE); \
	HH_SUB_PROTECTED_UNIT_EVENT(destroyed, UNIT_TYPE);

# define HH_UNIT_EVENT(UNIT_TYPE) \
	HH_SUB_UNIT_EVENT(created, UNIT_TYPE); \
	HH_SUB_UNIT_EVENT(completed, UNIT_TYPE); \
	HH_SUB_UNIT_EVENT(destroyed, UNIT_TYPE);

# define AGENT_HH_UNIT_EVENT(UNIT_TYPE) \
	HH_PROTECTED_UNIT_EVENT(UNIT_TYPE); \
	HH_UNIT_EVENT(UNIT_TYPE);

class Agent
{
public:

	Agent();
	virtual ~Agent();

	void request(Request* r); // priority is between 0 & 100

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
	virtual void protected_on_frame() = 0;

	virtual void protected_init();
	virtual void protected_clear();

	void try_request(Request* r);
	void on_request_ended(Request* r);


	AGENT_HH_UNIT_EVENT(UnitAgent);
	AGENT_HH_UNIT_EVENT(ArmyAgent);
	AGENT_HH_UNIT_EVENT(HQAgent);
	AGENT_HH_UNIT_EVENT(WorkerAgent);
	AGENT_HH_UNIT_EVENT(BuildingAgent);

private:

	Agent* parent_;
	std::queue<Request*> requests_to_remove_;
	std::set<Request*> requests_;
	std::set<Agent*> sub_agents_;
};

#include "agent.hxx"

#endif