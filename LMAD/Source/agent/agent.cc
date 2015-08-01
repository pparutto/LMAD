#include "agent.hh"

#include "requests/request.hh"

#include <iostream>

void Agent::request(Request* r)
{
	r->visit(this);
}

void Agent::accept(Request* r)
{
	std::cerr << "request error" << std::endl;
}