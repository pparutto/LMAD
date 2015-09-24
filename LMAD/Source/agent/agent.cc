#include "agent.hh"

#include "requests/requests.hh"

#include "unit-agent.hh"
#include "army-agent.hh"
#include "worker-agent.hh"
#include "hq-agent.hh"
#include "building-agent.hh"

#include <iostream>

#define CC_SUB_UNIT_EVENT(event_type, AGENT_TYPE) \
	void Agent::on_unit_##event_type(##AGENT_TYPE* a) \
	{ \
		protected_on_unit_##event_type(a); \
		\
		for (auto r : requests_) \
		{ \
			a->visit_request_on_unit_##event_type(r); \
		} \
		\
		for (auto sa : sub_agents_) \
		{ \
			a->visit_agent_on_unit_##event_type(sa); \
		} \
	} \
	\
	void Agent::protected_on_unit_##event_type(##AGENT_TYPE* a) \
	{ \
  }

#define CC_UNIT_EVENT(AGENT_TYPE) \
	CC_SUB_UNIT_EVENT(created, AGENT_TYPE) \
	CC_SUB_UNIT_EVENT(completed, AGENT_TYPE) \
	CC_SUB_UNIT_EVENT(destroyed, AGENT_TYPE)

Agent::Agent()
	: parent_(nullptr)
{

}

Agent::~Agent()
{
	//sub_agents_.clear();
}

void Agent::request(Request* r)
{
	requests_.insert(r);
}

void Agent::try_request(Request* r)
{
	r->visit(this);
}

/** 
	REQUESTS BEGIN
**/

void Agent::accept(Request* r)
{
	std::cerr << "request error" << std::endl;
}

void Agent::accept(PylonRequest* r)
{
	std::cerr << "request error" << std::endl;
}

/**
	REQUESTS END
**/

void Agent::on_frame()
{
	while (!requests_to_remove_.empty())
	{
		requests_.erase(requests_to_remove_.front());
		delete requests_to_remove_.front();
		requests_to_remove_.pop();
	}

	protected_on_frame();

	for (auto a : sub_agents_)
	{
		a->on_frame();
	}
	for (auto r : requests_)
	{
		r->on_frame();
		try_request(r);
	}
}

void Agent::on_request_ended(Request* r)
{
	requests_to_remove_.push(r);
}

void Agent::init()
{
	protected_init();
}

void Agent::clear()
{
	for (auto a : sub_agents_)
	{
		a->clear();
		delete a;
	}
	sub_agents_.clear();

	for (auto r : requests_)
	{
		r->clear();
		delete r;
	}
	protected_clear();
}

void Agent::protected_init()
{

}

void Agent::protected_clear()
{

}

CC_UNIT_EVENT(UnitAgent);
CC_UNIT_EVENT(ArmyAgent);
CC_UNIT_EVENT(WorkerAgent);
CC_UNIT_EVENT(HQAgent);
CC_UNIT_EVENT(BuildingAgent);
