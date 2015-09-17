#include "agent.hh"

#include "requests/requests.hh"
#include "unit-agent.hh"

#include <iostream>

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

void Agent::on_unit_created(UnitAgent* u)
{
	protected_on_unit_created(u);

	for (auto r : requests_)
	{
		r->on_unit_created(u);
	}

	for (auto a : sub_agents_)
	{
		a->on_unit_created(u);
	}
}

void Agent::on_unit_completed(UnitAgent* u)
{
	protected_on_unit_completed(u);

	for (auto r : requests_)
	{
		r->on_unit_completed(u);
	}

	for (auto a : sub_agents_)
	{
		a->on_unit_completed(u);
	}
}

void Agent::on_unit_destroyed(UnitAgent* u)
{
	protected_on_unit_destroyed(u);
	
	for (auto r : requests_)
	{
		r->on_unit_destroyed(u);
	}

	for (auto a : sub_agents_)
	{
		a->on_unit_destroyed(u);
	}
}

void Agent::protected_on_unit_created(UnitAgent* u)
{

}

void Agent::protected_on_unit_completed(UnitAgent* u)
{

}

void Agent::protected_on_unit_destroyed(UnitAgent* u)
{

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
	protected_on_frame();
	for (auto a : sub_agents_)
	{
		a->on_frame();
	}
	for (auto r : requests_)
	{
		try_request(r);
		r->on_frame();
	}
}

void Agent::on_request_ended(Request* r)
{
	requests_.erase(r);
	delete r;
}
