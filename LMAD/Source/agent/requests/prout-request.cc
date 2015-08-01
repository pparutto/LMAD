#include "prout-request.hh"

void ProutRequest::visit(Agent* agent)
{
	agent->accept(this);
}