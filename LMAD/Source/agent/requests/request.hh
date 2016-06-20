#ifndef REQUEST_HH_
# define REQUEST_HH_

# include "../unit-agents.hh"

# include "request-data.hh"

# define HH_SUB_REQUEST_UNIT_EVENT(UNIT_TYPE, EVENT_TYPE) \
	public: \
		virtual void on_unit_##EVENT_TYPE(UNIT_TYPE* u);

# define HH_REQUEST_UNIT_EVENT(UNIT_TYPE) \
	HH_SUB_REQUEST_UNIT_EVENT(UNIT_TYPE, created) \
	HH_SUB_REQUEST_UNIT_EVENT(UNIT_TYPE, completed) \
	HH_SUB_REQUEST_UNIT_EVENT(UNIT_TYPE, destroyed) \
	HH_SUB_REQUEST_UNIT_EVENT(UNIT_TYPE, morphing)

class Request
{
public:

#ifdef _DEBUG
	Request();
#endif

	virtual void visit(Agent* agent) = 0;

	void on_frame();

	RequestData* data_get() const;

	virtual void on_unit_show(BWAPI::Unit u);
	virtual void on_unit_hide(BWAPI::Unit u);
	virtual void on_enemy_destroy(BWAPI::Unit u);

	HH_REQUEST_UNIT_EVENT(UnitAgent);
	HH_REQUEST_UNIT_EVENT(WorkerAgent);
	HH_REQUEST_UNIT_EVENT(ArmyAgent);
	HH_REQUEST_UNIT_EVENT(BuildingAgent);

	void clear();

protected:
	virtual void protected_clear();

protected:
	RequestData* data_;
};

# include "request.hxx"

#endif