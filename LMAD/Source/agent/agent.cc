#include "agent.hh"

#include "requests/request.hh"

#include <iostream>

void Agent::request(Request* r, unsigned priority)
{
	requests_.insert(std::make_pair(r, priority));
}

void Agent::try_request(Request* r, unsigned priority)
{
	r->visit(this, priority);
}

void Agent::accept(Request* r, unsigned priority)
{
	std::cerr << "request error" << std::endl;
}