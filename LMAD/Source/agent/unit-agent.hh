#ifndef UNIT_AGENT_HH_
# define UNIT_AGENT_HH_

# include "agent.hh"

class UnitAgent : virtual public Agent
{
public:
	UnitAgent(BWAPI::Unit unit);
	virtual ~UnitAgent();

	virtual void visit_agent_on_unit_created(Agent* a) = 0;
	virtual void visit_agent_on_unit_completed(Agent* a) = 0;
	virtual void visit_agent_on_unit_destroyed(Agent* a) = 0;

	virtual void visit_request_on_unit_created(Request* r) = 0;
	virtual void visit_request_on_unit_completed(Request* r) = 0;
	virtual void visit_request_on_unit_destroyed(Request* r) = 0;

public:

	BWAPI::Unit unit_get() const;

protected:

	virtual void protected_clear() override;

private:

	BWAPI::Unit unit_;
};

# include "unit-agent.hxx"

# define VISIT_DECLARATIONS  \
	public: \
		virtual void visit_agent_on_unit_created(Agent* a) override;\
		virtual void visit_agent_on_unit_completed(Agent* a) override;\
		virtual void visit_agent_on_unit_destroyed(Agent* a) override;\
		\
		virtual void visit_request_on_unit_created(Request* r) override;\
		virtual void visit_request_on_unit_completed(Request* r) override;\
		virtual void visit_request_on_unit_destroyed(Request* r) override;

# define VISIT_DEFINITIONS(AGENT_TYPE) \
	\
void AGENT_TYPE::visit_agent_on_unit_created(Agent* a)\
{\
	a->on_unit_created(this);\
}\
	\
void AGENT_TYPE::visit_agent_on_unit_completed(Agent* a)\
{\
	a->on_unit_completed(this);\
}\
	\
void AGENT_TYPE::visit_agent_on_unit_destroyed(Agent* a)\
{\
	a->on_unit_destroyed(this);	\
}\
	\
void AGENT_TYPE::visit_request_on_unit_created(Request* r)\
{\
	r->on_unit_created(this);	\
}\
	\
void AGENT_TYPE::visit_request_on_unit_completed(Request* r)\
{\
	r->on_unit_completed(this);\
}\
	\
void AGENT_TYPE::visit_request_on_unit_destroyed(Request* r)\
{\
	r->on_unit_destroyed(this);	\
}

#endif