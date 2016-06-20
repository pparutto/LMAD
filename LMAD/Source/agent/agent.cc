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
	CC_SUB_UNIT_EVENT(destroyed, AGENT_TYPE) \
	CC_SUB_UNIT_EVENT(morphing, AGENT_TYPE)

Agent::Agent()
	: last_frame_execution_(-1)
	, can_suicid_(true)
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

void Agent::accept(BuildingRequest* r)
{
	std::cerr << "request error" << std::endl;
}

/**
	REQUESTS END
**/

void Agent::on_frame()
{
	if (parents_.size() == 0 && can_suicid_)
	{
		clear();
		// Haha
		delete this;
		return;
	}

	int current_frame = BWAPI::Broodwar->getFrameCount();
	if (current_frame == last_frame_execution_)
	{
		return;
	}

	last_frame_execution_ = current_frame;

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
		a->remove_parent(this);
	}

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

void Agent::on_unit_show(BWAPI::Unit u)
{
	protected_on_unit_show(u);

	for (auto r : requests_)
	{
		r->on_unit_show(u);
	}

	for (auto a : sub_agents_)
	{
		a->on_unit_show(u);
	}
}

void Agent::protected_on_unit_show(BWAPI::Unit u)
{

}

void Agent::on_unit_hide(BWAPI::Unit u)
{
	protected_on_unit_hide(u);

	for (auto r : requests_)
	{
		r->on_unit_hide(u);
	}

	for (auto a : sub_agents_)
	{
		a->on_unit_hide(u);
	}
}

void Agent::protected_on_unit_hide(BWAPI::Unit u)
{

}

void Agent::on_enemy_unit_destroyed(BWAPI::Unit u)
{
	protected_on_enemy_unit_destroyed(u);

	for (auto r : requests_)
	{
		r->on_enemy_destroy(u);
	}

	for (auto a : sub_agents_)
	{
		a->on_enemy_unit_destroyed(u);
	}
}

void Agent::protected_on_enemy_unit_destroyed(BWAPI::Unit u)
{

}

CC_UNIT_EVENT(UnitAgent);
CC_UNIT_EVENT(ArmyAgent);
CC_UNIT_EVENT(WorkerAgent);
CC_UNIT_EVENT(BuildingAgent);
