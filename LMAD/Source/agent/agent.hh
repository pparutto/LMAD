#ifndef AGENT_HH_
# define AGENT_HH_

# include <utility>
# include <set>
# include <queue>

# include <BWAPI/unit.h>

class Request;

# include "requests/requests-fw.hh"
# include "unit-agents-fw.hh"

# define HH_SUB_PROTECTED_UNIT_EVENT(event_type, UNIT_TYPE) \
	protected: \
	virtual void protected_on_unit_##event_type(UNIT_TYPE* a);

# define HH_SUB_UNIT_EVENT(event_type, UNIT_TYPE) \
	public: \
	void on_unit_##event_type(UNIT_TYPE* a);

# define HH_PROTECTED_UNIT_EVENT(UNIT_TYPE) \
	HH_SUB_PROTECTED_UNIT_EVENT(created, UNIT_TYPE); \
	HH_SUB_PROTECTED_UNIT_EVENT(completed, UNIT_TYPE); \
	HH_SUB_PROTECTED_UNIT_EVENT(destroyed, UNIT_TYPE); \
	HH_SUB_PROTECTED_UNIT_EVENT(morphing, UNIT_TYPE);

# define HH_UNIT_EVENT(UNIT_TYPE) \
	HH_SUB_UNIT_EVENT(created, UNIT_TYPE); \
	HH_SUB_UNIT_EVENT(completed, UNIT_TYPE); \
	HH_SUB_UNIT_EVENT(destroyed, UNIT_TYPE); \
	HH_SUB_UNIT_EVENT(morphing, UNIT_TYPE);

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
	virtual void accept(BuildingRequest* r);

	/**
		REQUESTS END
	**/

	void on_frame();

	void init();

public:

	void add_parent(Agent* parent);
	void remove_parent(Agent* parent);
	std::set<Agent*> parents_get() const;

	void add_sub_agent(Agent* agent);
	void remove_sub_agent(Agent* agent);

	void on_unit_show(BWAPI::Unit u);
	void on_unit_hide(BWAPI::Unit u);
	void on_enemy_unit_destroyed(BWAPI::Unit u);

	void can_suicid_set(const bool value);

protected:
	virtual void protected_on_frame() = 0;

	virtual void protected_init();
	virtual void protected_clear();
	void clear();

	virtual void protected_on_unit_show(BWAPI::Unit u);
	virtual void protected_on_unit_hide(BWAPI::Unit u);
	virtual void protected_on_enemy_unit_destroyed(BWAPI::Unit u);

	void try_request(Request* r);
	void on_request_ended(Request* r);


	AGENT_HH_UNIT_EVENT(UnitAgent);
	AGENT_HH_UNIT_EVENT(ArmyAgent);
	AGENT_HH_UNIT_EVENT(WorkerAgent);
	AGENT_HH_UNIT_EVENT(BuildingAgent);

private:

	std::set<Agent*> parents_;
	std::queue<Request*> requests_to_remove_;
	std::set<Request*> requests_;
	std::set<Agent*> sub_agents_;

	int last_frame_execution_;
	bool can_suicid_;
};

#include "agent.hxx"

#endif